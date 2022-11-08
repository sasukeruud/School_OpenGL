#include <iostream>

#include "lab4.h"

#define GLM_ENABLE_EXPERIMENTAL

void lab4::processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, true);
	delay(100);
}

GLuint LoadTexture(std::string imagePath, int slot) {
	std::string filePath = std::string(TEXTURES_DIR) + imagePath;

	int width, height, bpp;
	auto *pixels = stbi_load(filePath.c_str(), &width, &height, &bpp, STBI_rgb_alpha);
	if (!pixels) {
		std::cout << "Failed to load texture" << std::endl;
		return EXIT_FAILURE;
	}

	GLuint tex;
	glGenTextures(1, &tex);
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	if (pixels) stbi_image_free(pixels);

	return tex;
}


GLuint LoadCubeMap(std::string imagePath, int slot) {
	std::string filePath = std::string(TEXTURES_DIR) + imagePath;

	int width, height, bpp;
	auto* pixels = stbi_load(filePath.c_str(), &width, &height, &bpp, STBI_rgb_alpha);
	if (!pixels) {
		std::cout << "Failed to load texture" << std::endl;
		return EXIT_FAILURE;
	}

	GLuint tex;
	glGenTextures(1, &tex);
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_CUBE_MAP, tex);

	for (unsigned int i = 0; i < 6; i++)
	{
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
	}

	//Wrapping
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_REPEAT);
	//Filtering
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

}

unsigned int lab4::Run() {
	int boardSize = 8;
	std::vector<glm::vec4> vertices; //Full grid layout
	std::vector<glm::vec3> verticies_color;
	std::vector<glm::uvec3> indices; //Indicies
	std::vector<glm::vec2> white; //Only white spaces
	std::vector<glm::vec2> white_texture;
	std::vector<glm::vec2> black; // Only black spaces
	std::vector<glm::vec2> black_texture;
	GeometricTools::GenGridTexture<std::vector<glm::vec4>, std::vector<glm::uvec3>>(boardSize, vertices, indices);

	auto projectionMatrix = glm::perspective(glm::radians(45.0f), 1.0f, 1.0f, -10.f);
	auto viewMatrix = glm::lookAt(glm::vec3(0, 0, 8), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

	glm::mat4 chessBoardMatrix = glm::mat4(1.0f);
	auto chessBoardRotation = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(1.0f, .0f, .0f));
	auto chessBoardTranslation = glm::translate(glm::mat4(1.0f), glm::vec3(-3.0f, -.5f, 0.0f));
	auto chessBoardScale = glm::scale(glm::mat4(1.0f), glm::vec3(8.f,8.f,8.f));
	chessBoardMatrix = chessBoardTranslation * chessBoardRotation * chessBoardScale;

	bool whiteColor = true;
	/*
	* Loop for checking which vertex is for which color
	* Uses the maping of indicies from the grid layout to find the correct position for the vertex data
	*/
	for (int i = 0; i < indices.size() - 1; i++)
	{
		if (whiteColor) {
			white.push_back(glm::vec2(vertices[indices[i].x].x, vertices[indices[i].x].y));
			white.push_back(glm::vec2(vertices[indices[i].y].x, vertices[indices[i].y].y));
			white.push_back(glm::vec2(vertices[indices[i].z].x, vertices[indices[i].z].y));

			white_texture.push_back(glm::vec2(vertices[indices[i].x].z, vertices[indices[i].x].w));
			white_texture.push_back(glm::vec2(vertices[indices[i].y].z, vertices[indices[i].y].w));
			white_texture.push_back(glm::vec2(vertices[indices[i].z].z, vertices[indices[i].z].w));

			white.push_back(glm::vec2(vertices[indices[i + 1].x].x, vertices[indices[i + 1].x].y));
			white.push_back(glm::vec2(vertices[indices[i + 1].y].x, vertices[indices[i + 1].y].y));
			white.push_back(glm::vec2(vertices[indices[i + 1].z].x, vertices[indices[i + 1].z].y));
			
			white_texture.push_back(glm::vec2(vertices[indices[i + 1].x].z, vertices[indices[i + 1].x].w));
			white_texture.push_back(glm::vec2(vertices[indices[i + 1].y].z, vertices[indices[i + 1].y].w));
			white_texture.push_back(glm::vec2(vertices[indices[i + 1].z].z, vertices[indices[i + 1].z].w));

			whiteColor = false;
			i++; //Moves one additonall block to the right
		}
		else {
			black.push_back(glm::vec2(vertices[indices[i].x].x, vertices[indices[i].x].y));
			black.push_back(glm::vec2(vertices[indices[i].y].x, vertices[indices[i].y].y));
			black.push_back(glm::vec2(vertices[indices[i].z].x, vertices[indices[i].z].y));

			black_texture.push_back(glm::vec2(vertices[indices[i].x].z, vertices[indices[i].x].w));
			black_texture.push_back(glm::vec2(vertices[indices[i].y].z, vertices[indices[i].y].w));
			black_texture.push_back(glm::vec2(vertices[indices[i].z].z, vertices[indices[i].z].w));

			black.push_back(glm::vec2(vertices[indices[i + 1].x].x, vertices[indices[i + 1].x].y));
			black.push_back(glm::vec2(vertices[indices[i + 1].y].x, vertices[indices[i + 1].y].y));
			black.push_back(glm::vec2(vertices[indices[i + 1].z].x, vertices[indices[i + 1].z].y));

			black_texture.push_back(glm::vec2(vertices[indices[i + 1].x].z, vertices[indices[i + 1].x].w));
			black_texture.push_back(glm::vec2(vertices[indices[i + 1].y].z, vertices[indices[i + 1].y].w));
			black_texture.push_back(glm::vec2(vertices[indices[i + 1].z].z, vertices[indices[i + 1].z].w));
			
			whiteColor = true;
			i++; //Moves one additonall block to the right
		}
		if (vertices[indices[i].x].x == 1 - (float)1/boardSize) whiteColor = !whiteColor; //If the end of row is meet
	}
	
	auto vao_white = std::make_shared<VertexArray>();
	auto vao_black = std::make_shared<VertexArray>();
	auto vao_selector = std::make_shared<VertexArray>();

	vao_white->Bind();
	auto vbo = std::make_shared<VertexBuffer>();
	auto vbo_color = std::make_shared<VertexBuffer>();

	vbo->SetData(glm::value_ptr(white[0]), (int)white.size() * sizeof(glm::vec3));
	vbo->Bind();
	vao_white->AddVertexBuffer(0, 2, *vbo);
	vbo->Unbind();
	
	for (int i = 0; i < white.size(); i++)
	{
		verticies_color.push_back(glm::vec3(ColorTools::FullColor[0], ColorTools::FullColor[0], ColorTools::FullColor[0]));
	}

	//vbo_color->SetData(glm::value_ptr(verticies_color[0]), (int)verticies_color.size() * sizeof(glm::vec3));
	vbo_color->SetData(glm::value_ptr(white_texture[0]), white_texture.size() * sizeof(glm::vec2));
	vbo_color->Bind();
	vao_white->AddVertexBuffer(1, 2, *vbo_color);
	vbo_color->Unbind();

	vao_black->Bind();
	vbo->SetData(glm::value_ptr(black[0]), (int)black.size() * sizeof(glm::vec2));
	vbo->Bind();
	vao_black->AddVertexBuffer(0, 2, *vbo);
	vbo->Unbind();

	verticies_color.clear();
	
	for (int i = 0; i < white.size(); i++)
	{
		verticies_color.push_back(glm::vec3(ColorTools::NoneColor[0], ColorTools::NoneColor[0], ColorTools::NoneColor[0]));
	}

	//vbo_color->SetData(glm::value_ptr(verticies_color[0]), (int)verticies_color.size() * sizeof(glm::vec3));
	vbo_color->SetData(glm::value_ptr(black_texture[0]), black_texture.size() * sizeof(glm::vec2));
	vbo_color->Bind();
	vao_black->AddVertexBuffer(1, 2, *vbo_color);
	vbo_color->Unbind();

	vao_selector->Bind();
	auto vbo_square = std::make_shared<VertexBuffer>();

	/*
	vbo_square->Bind();
	vbo_square->SetData(GeometricTools::UnitCube, sizeof(GeometricTools::UnitCube));
	vao_selector->AddVertexBuffer(0, 3, *vbo_square);

	auto vbo_square_color = std::make_shared<VertexBuffer>();
	vbo_square_color->Bind();
	vbo_square_color->SetData(GeometricTools::ColorSquare2D, sizeof(GeometricTools::ColorSquare2D));
	vao_selector->AddVertexBuffer(1,3,*vbo_square_color);*/

	const std::string& vertexShaderCube = R"(
	#version 460

	#define center vec4(-0.5,-0.5,0,0)
	
	layout (location = 0) in vec3 pos;
	layout (location = 1) in vec3 color;
	
	uniform mat4 u_projection;
	uniform mat4 u_view;
	uniform mat4 model;

	out vec3 vs_position;
	out vec3 vs_color;

	void main()
	{
		gl_Position = u_projection * u_view * model * vec4(pos,1.0);
		vs_position = pos;
		vs_color = color;
	}
)";

	const std::string& vertexShaderFloor = R"(
	#version 460

	#define center vec4(-0.5,-0.5,0,0)
	
	layout (location = 0) in vec2 pos;
	layout (location = 1) in vec2 tcoords;
	
	uniform mat4 u_projection;
	uniform mat4 u_view;
	uniform mat4 model;

	out vec2 vs_tcoords; 

	void main()
	{
		gl_Position = u_projection * u_view * model * vec4(pos,0.0,1.0);
		vs_tcoords = tcoords;
	}
)";

	const std::string& fragmentShaderCube = R"(
	#version 460 core

	layout(binding=1) uniform samplerCube uTexture;

	out vec4 FragColor;

	in vec3 vs_position;
	in vec3 vs_color;

	void main()
	{
			FragColor = texture(uTexture, vs_position); 
	})";

	const std::string& fragmentShaderFloor = R"(
	#version 460 core

	out vec4 FragColor;

	in vec2 vs_tcoords;
	layout(binding = 0) uniform sampler2D u_floorTextureSampler;

	void main()
	{
			FragColor = texture(u_floorTextureSampler, vs_tcoords);
	}
)";

	auto vao_cube = std::make_shared<VertexArray>();
	vao_cube->Bind();

	auto vbo_cube = std::make_shared<VertexBuffer>();
	auto vbo_vube_color = std::make_shared<VertexBuffer>();

	vbo_cube->SetData(GeometricTools::UnitCube, sizeof(GeometricTools::UnitCube));
	vbo_cube->Bind();
	vao_cube->AddVertexBuffer(0, 3, *vbo_cube);
	
	vbo_vube_color->SetData(ColorTools::UnitCubeDefaultColor, sizeof(ColorTools::UnitCubeDefaultColor));
	vbo_vube_color->Bind();
	vao_cube->AddVertexBuffer(1, 3, *vbo_vube_color);

	auto shader = std::make_shared<Shader>(vertexShaderFloor, fragmentShaderFloor);
	auto shader1 = std::make_shared<Shader>(vertexShaderCube, fragmentShaderCube);

	shader->Bind();
	shader->UseShader();
	shader->UploadUniformMatrix4(shader->UniformLocation("model"), chessBoardMatrix);
	shader->UploadUniformMatrix4(shader->UniformLocation("u_view"), viewMatrix);
	shader->UploadUniformMatrix4(shader->UniformLocation("u_projection"), projectionMatrix);
	shader->UploadUniformInt(shader->UniformLocation("u_floorTextureSampler"), 0);
	
	shader1->Bind();
	shader1->UseShader();

	glm::mat4 cubeMatrix = glm::mat4(1.0f);
	auto cubeRotation = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(1.0f, .0f, .0f));
	auto cubeTranslation = glm::translate(glm::mat4(1.0f), glm::vec3(.0f, -.5f, 0.0f));
	auto cubeScale = glm::scale(glm::mat4(1.0f), glm::vec3(1.f, 1.f, 1.f));
	chessBoardMatrix = cubeTranslation * cubeRotation * cubeScale;

	auto cubeViewMatrix = glm::lookAt(glm::vec3(0, 0, 8), glm::vec3(0, -.5f, 0), glm::vec3(0, 1, 0));

	auto uniform_shader1_model = shader1->UniformLocation("model");
	shader1->UploadUniformMatrix4(uniform_shader1_model, cubeMatrix);
	shader1->UploadUniformMatrix4(shader1->UniformLocation("u_view"), cubeViewMatrix);
	shader1->UploadUniformMatrix4(shader1->UniformLocation("u_projection"), projectionMatrix);
	
	RenderCommands::DepthRendering();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC0_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glm::vec3 background = glm::vec3(ColorTools::FullColor[0] * 0.5f, ColorTools::FullColor[0] * 0.0f, ColorTools::FullColor[0] * 0.0f);
	RenderCommands::SetClearColor(background);
	while (!glfwWindowShouldClose(window)) {
		processInput(window);
		shader->UseShader();
		auto cubeMatrixRotationX = glm::mat4(1.f);
		auto cubeMatrixRotationY = glm::mat4(1.f);
		LoadTexture("wall.jpg",0);
		RenderCommands::Clear();
		//White squares
		vao_white->Bind();
		RenderCommands::DrawTriangle(RenderCommands::SquareSize * white.size());
		vao_white->Unbind();

		//Black squares
		vao_black->Bind();
		RenderCommands::DrawTriangle(RenderCommands::SquareSize * black.size());
		vao_black->Unbind();

		//Selector on screen
		/*
		vao_selector->Bind();
		RenderCommands::DrawTriangle(RenderCommands::SquareSize);
		vao_selector->Unbind();
		*/

		vao_cube->Bind();
		shader1->UseShader();
		LoadCubeMap("awesomeface.png", 1);
		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_TRUE) {
			cubeMatrixRotationY = glm::rotate(glm::mat4(1.f), glm::radians(-8.0f), glm::vec3(1.0f, .0f, .0f));
		}
		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_TRUE) {
			cubeMatrixRotationY = glm::rotate(glm::mat4(1.f), glm::radians(8.0f), glm::vec3(1.0f, .0f, .0f));
		}
		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_TRUE) {
			cubeMatrixRotationX = glm::rotate(glm::mat4(1.f), glm::radians(8.0f), glm::vec3(.0f, 1.0f, .0f));
		}
		if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_TRUE) {
			cubeMatrixRotationX = glm::rotate(glm::mat4(1.f), glm::radians(-8.0f), glm::vec3(.0f, 1.0f, .0f));
		}
		cubeMatrix = cubeMatrixRotationX * cubeMatrixRotationY * cubeMatrix;
		shader1->UploadUniformMatrix4(uniform_shader1_model, cubeMatrix);
		delay(10);
		//RenderCommands::SetWireframeMode();
		RenderCommands::DrawCube();
		//RenderCommands::SetFillMode();
		//glDrawArrays(GL_TRIANGLES, 0, 36);
		vao_cube->Unbind();

		glfwPollEvents();
		glfwSwapBuffers(window);
	}
	Destroy();

	return EXIT_SUCCESS;
}
