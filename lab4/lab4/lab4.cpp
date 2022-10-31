#include <iostream>

#include "lab4.h"

#define GLM_ENABLE_EXPERIMENTAL

void lab4::processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, true);
	delay(100);
}

unsigned int lab4::Run() {
	int boardSize = 16;
	std::vector<glm::vec3> vertices; //Full grid layout
	std::vector<glm::vec3> verticies_color;
	std::vector<glm::uvec3> indices; //Indicies
	std::vector<glm::vec3> white; //Only white spaces
	std::vector<glm::vec3> black; // Only black spaces
	GeometricTools::GenGrid<std::vector<glm::vec3>, std::vector<glm::uvec3>>(boardSize, vertices, indices);

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
			white.push_back(glm::vec3(vertices[indices[i].x].x, vertices[indices[i].x].y, vertices[indices[i].x].z));
			white.push_back(glm::vec3(vertices[indices[i].y].x, vertices[indices[i].y].y, vertices[indices[i].y].z));
			white.push_back(glm::vec3(vertices[indices[i].z].x, vertices[indices[i].z].y, vertices[indices[i].z].z));

			white.push_back(glm::vec3(vertices[indices[i + 1].x].x, vertices[indices[i + 1].x].y, vertices[indices[i + 1].x].z));
			white.push_back(glm::vec3(vertices[indices[i + 1].y].x, vertices[indices[i + 1].y].y, vertices[indices[i + 1].y].z));
			white.push_back(glm::vec3(vertices[indices[i + 1].z].x, vertices[indices[i + 1].z].y, vertices[indices[i + 1].z].z));
			
			whiteColor = false;
			i++; //Moves one additonall block to the right
		}
		else {
			black.push_back(glm::vec3(vertices[indices[i].x].x, vertices[indices[i].x].y, vertices[indices[i].x].z));
			black.push_back(glm::vec3(vertices[indices[i].y].x, vertices[indices[i].y].y, vertices[indices[i].y].z));
			black.push_back(glm::vec3(vertices[indices[i].z].x, vertices[indices[i].z].y, vertices[indices[i].z].z));

			black.push_back(glm::vec3(vertices[indices[i + 1].x].x, vertices[indices[i + 1].x].y, vertices[indices[i + 1].x].z));
			black.push_back(glm::vec3(vertices[indices[i + 1].y].x, vertices[indices[i + 1].y].y, vertices[indices[i + 1].y].z));
			black.push_back(glm::vec3(vertices[indices[i + 1].z].x, vertices[indices[i + 1].z].y, vertices[indices[i + 1].z].z));
			
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
	vao_white->AddVertexBuffer(0, 3, *vbo);
	vbo->Unbind();
	
	for (int i = 0; i < white.size(); i++)
	{
		verticies_color.push_back(glm::vec3(ColorTools::FullColor[0], ColorTools::FullColor[0], ColorTools::FullColor[0]));
	}

	vbo_color->SetData(glm::value_ptr(verticies_color[0]), (int)verticies_color.size() * sizeof(glm::vec3));
	vbo_color->Bind();
	vao_white->AddVertexBuffer(1, 3, *vbo_color);
	vbo_color->Unbind();

	vao_black->Bind();
	vbo->SetData(glm::value_ptr(black[0]), (int)black.size() * sizeof(glm::vec3));
	vbo->Bind();
	vao_black->AddVertexBuffer(0, 3, *vbo);
	vbo->Unbind();

	verticies_color.clear();
	
	for (int i = 0; i < white.size(); i++)
	{
		verticies_color.push_back(glm::vec3(ColorTools::NoneColor[0], ColorTools::NoneColor[0], ColorTools::NoneColor[0]));
	}

	vbo_color->SetData(glm::value_ptr(verticies_color[0]), (int)verticies_color.size() * sizeof(glm::vec3));
	vbo_color->Bind();
	vao_black->AddVertexBuffer(1, 3, *vbo_color);
	vbo_color->Unbind();

	vao_selector->Bind();
	auto vbo_square = std::make_shared<VertexBuffer>();

	vbo_square->Bind();
	vbo_square->SetData(GeometricTools::UnitCube, sizeof(GeometricTools::UnitCube));
	vao_selector->AddVertexBuffer(0, 3, *vbo_square);

	auto vbo_square_color = std::make_shared<VertexBuffer>();
	vbo_square_color->Bind();
	vbo_square_color->SetData(GeometricTools::ColorSquare2D, sizeof(GeometricTools::ColorSquare2D));
	vao_selector->AddVertexBuffer(1,3,*vbo_square_color);

	const std::string& vertexShaderSrc = R"(
	#version 460

	#define center vec4(-0.5,-0.5,0,0)
	
	layout (location = 0) in vec3 pos;
	layout (location = 1) in vec3 color;
	
	uniform mat4 u_projection;
	uniform mat4 u_view;
	uniform mat4 model;

	//flat removes inteporlotian
	out vec3 ourColor; 

	void main()
	{
		gl_Position = u_projection * u_view * model * vec4(pos,1.0);
		//gl_Position = vec4(pos,1.0) + center;
		ourColor = vec3(color.x,color.y,color.z);
	}
)";

	const std::string& fragmentShaderSrc = R"(
	#version 460 core

	#define M_PI 3.14159265

	out vec4 FragColor;

	//flat removes inteporlotian
	in vec3 ourColor;

	void main()
	{
			FragColor = vec4(ourColor, 1.0);
	})";

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

	auto shader = std::make_shared<Shader>(vertexShaderSrc, fragmentShaderSrc);
	auto shader1 = std::make_shared<Shader>(vertexShaderSrc, fragmentShaderSrc);

	shader->Bind();
	shader->UseShader();
	shader->UploadUniformMatrix4(shader->UniformLocation("model"), chessBoardMatrix);
	shader->UploadUniformMatrix4(shader->UniformLocation("u_view"), viewMatrix);
	shader->UploadUniformMatrix4(shader->UniformLocation("u_projection"), projectionMatrix);
	
	shader1->Bind();
	shader1->UseShader();

	glm::mat4 cubeMatrix = glm::mat4(1.0f);
	auto cubeRotation = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(1.0f, .0f, .0f));
	auto cubeTranslation = glm::translate(glm::mat4(1.0f), glm::vec3(.0f, -.5f, 0.0f));
	auto cubeScale = glm::scale(glm::mat4(1.0f), glm::vec3(1.f, 1.f, 1.f));
	chessBoardMatrix = cubeTranslation * cubeRotation * cubeScale;

	auto uniform_shader1_model = shader1->UniformLocation("model");
	shader1->UploadUniformMatrix4(uniform_shader1_model, cubeMatrix);
	shader1->UploadUniformMatrix4(shader1->UniformLocation("u_view"), viewMatrix);
	shader1->UploadUniformMatrix4(shader1->UniformLocation("u_projection"), projectionMatrix);
	
	RenderCommands::DepthRendering();

	glm::vec3 background = glm::vec3(ColorTools::FullColor[0] * 0.5f, ColorTools::FullColor[0] * 0.0f, ColorTools::FullColor[0] * 0.0f);
	RenderCommands::SetClearColor(background);
	while (!glfwWindowShouldClose(window)) {
		processInput(window);
		shader->UseShader();
		
		RenderCommands::Clear();
		//White squares
		vao_white->Bind();
		glDrawArrays(GL_TRIANGLES, 0, 6 * white.size());
		vao_white->Unbind();

		//Black squares
		vao_black->Bind();
		glDrawArrays(GL_TRIANGLES, 0, 6 * black.size());
		vao_black->Unbind();

		//Selector on screen
		vao_selector->Bind();
		glDrawArrays(GL_TRIANGLES, 0, 6);
		vao_selector->Unbind();

		vao_cube->Bind();
		shader1->UseShader();
		
		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_TRUE) {
			cubeMatrix = glm::rotate(cubeMatrix, glm::radians(50.0f), glm::vec3(1.0f, 1 / boardSize, .0f));
			shader1->UploadUniformMatrix4(uniform_shader1_model, cubeMatrix);
		}
		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_TRUE) {
			cubeMatrix = glm::rotate(cubeMatrix, glm::radians(-50.0f), glm::vec3(1.0f, 1 / boardSize, .0f));
			shader1->UploadUniformMatrix4(uniform_shader1_model, cubeMatrix);
		}
		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_TRUE) {
			cubeMatrix = glm::rotate(cubeMatrix, glm::radians(50.0f), glm::vec3(1 / boardSize, 1.0f, .0f));
			shader1->UploadUniformMatrix4(uniform_shader1_model, cubeMatrix);
		}
		if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_TRUE) {
			cubeMatrix = glm::rotate(cubeMatrix, glm::radians(-50.0f), glm::vec3(1 / boardSize, 1.0f, .0f));
			shader1->UploadUniformMatrix4(uniform_shader1_model, cubeMatrix);
		}
		if (glfwGetKey(window, GLFW_KEY_R) == GLFW_TRUE) {
			cubeMatrix = glm::rotate(cubeMatrix, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(1.0f, 1.0f, .0f));
			shader1->UploadUniformMatrix4(uniform_shader1_model, cubeMatrix);
		}
		delay(10);
		//RenderCommands::SetWireframeMode();
		glDrawArrays(GL_TRIANGLES, 0, 36);
		//RenderCommands::SetFillMode();
		//glDrawArrays(GL_TRIANGLES, 0, 36);
		vao_cube->Unbind();

		glfwPollEvents();
		glfwSwapBuffers(window);
	}
	Destroy();

	return EXIT_SUCCESS;
}
