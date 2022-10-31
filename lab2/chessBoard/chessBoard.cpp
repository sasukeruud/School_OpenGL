#include <iostream>

#include "chessBoard.h"

#define GLM_ENABLE_EXPERIMENTAL

void chessBoard::processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, true);
	delay(100);
}

unsigned int chessBoard::Run() {
	int boardSize = 8;
	std::vector<glm::vec3> vertices; //Full grid layout
	std::vector<glm::vec3> verticies_color; //Color for each vertex
	std::vector<glm::uvec3> indices; //Indicies
	std::vector<glm::vec3> white; //Only white spaces
	std::vector<glm::vec3> black; // Only black spaces

	GeometricTools::GenGrid<std::vector<glm::vec3>, std::vector<glm::uvec3>>(boardSize, vertices, indices);

	//That is needed for translate
	glm::mat4 trans = glm::mat4(1.0f);
	trans = glm::translate(trans, glm::vec3(-.5f, -.5f, 0.0f));
	//trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(.0f, .0f, 1.0f));
	//trans = glm::scale(trans, glm::vec3(.5f,.5f,.5f));

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
	
	auto vao_white = VertexArray();
	auto vao_black = VertexArray();
	auto vao_selector = VertexArray();

	vao_white.Bind();
	auto vbo = VertexBuffer();
	auto vbo_color = VertexBuffer();

	vbo.SetData(glm::value_ptr(white[0]), (int)white.size() * sizeof(glm::vec3));
	vbo.Bind();
	vao_white.AddVertexBuffer(0, 3, vbo);
	vbo.Unbind();
	
	for (int i = 0; i < white.size(); i++)
	{
		verticies_color.push_back(glm::vec3(ColorTools::FullColor[0], ColorTools::FullColor[0], ColorTools::FullColor[0]));
	}

	vbo_color.SetData(glm::value_ptr(verticies_color[0]), (int)verticies_color.size() * sizeof(glm::vec3));
	vbo_color.Bind();
	vao_white.AddVertexBuffer(1, 3, vbo_color);

	vao_black.Bind();
	vbo.SetData(glm::value_ptr(black[0]), (int)black.size() * sizeof(glm::vec3));
	vbo.Bind();
	vao_black.AddVertexBuffer(0, 3, vbo);
	vbo.Unbind();

	verticies_color.clear();
	
	for (int i = 0; i < white.size(); i++)
	{
		verticies_color.push_back(glm::vec3(ColorTools::NoneColor[0], ColorTools::NoneColor[0], ColorTools::NoneColor[0]));
	}

	vbo_color.SetData(glm::value_ptr(verticies_color[0]), (int)verticies_color.size() * sizeof(glm::vec3));
	vbo_color.Bind();
	vao_black.AddVertexBuffer(1, 3, vbo_color);

	vao_selector.Bind();
	auto vbo_square = VertexBuffer();

	/*
	* takes the indecies value for 0 to be able to get the vertex value for that position
	*/
	float squareCurosr[6*3] = { vertices[indices[0].x].x,vertices[indices[0].x].y,vertices[indices[0].x].z,
							vertices[indices[0].y].x, vertices[indices[0].y].y,vertices[indices[0].y].z,
							vertices[indices[0].z].x, vertices[indices[0].z].y,vertices[indices[0].z].z,

							vertices[indices[1].x].x,vertices[indices[1].x].y,vertices[indices[1].x].z,
							vertices[indices[1].y].x, vertices[indices[1].y].y,vertices[indices[1].y].z ,
							vertices[indices[1].z].x, vertices[indices[1].z].y,vertices[indices[1].z].z
							 };

	vbo_square.Bind();
	//Fix scaling in shader
	vbo_square.SetData(GeometricTools::UnitSquare2D, sizeof(GeometricTools::UnitSquare2D));
	vbo_square.Bind();
	vao_selector.AddVertexBuffer(0, 3, vbo_square);

	auto vbo_square_color = VertexBuffer();
	vbo_square_color.Bind();
	vbo_square_color.SetData(GeometricTools::ColorSquare2D, sizeof(GeometricTools::ColorSquare2D));
	vbo_square_color.Bind();
	vao_selector.AddVertexBuffer(1,3,vbo_square_color);

	const std::string& vertexShaderSrc = R"(
	#version 460

	#define center vec4(-0.5,-0.5,0,0)
	
	layout (location = 0) in vec3 pos;
	layout (location = 1) in vec3 color;

	uniform mat4 transform;

	flat out vec3 ourColor; 

	void main()
	{
		gl_Position = transform * vec4(pos,1.0);
		ourColor = vec3(color.x,color.y,color.z);
	}
)";

	const std::string& fragmentShaderSrc = R"(
	#version 460 core

	#define M_PI 3.14159265

	out vec4 FragColor;

	//flat removes inteporlotian
	flat in vec3 ourColor;

	void main()
	{
			FragColor = vec4(ourColor, 1.0);
	})";

	auto shader = Shader::Shader(vertexShaderSrc, fragmentShaderSrc);
	auto shader1 = Shader::Shader(vertexShaderSrc, fragmentShaderSrc);
	shader.Bind();
	
	shader.UseShader();
	shader1.Bind();
	auto uniform1 = shader1.UniformLocation("transform");
	glUniformMatrix4fv(uniform1, 1, GL_FALSE, glm::value_ptr(trans));
	
	int pos = 0;

	while (!glfwWindowShouldClose(window)) {
		processInput(window);
		//WireframeMode();
		shader.UseShader();
		glClearColor(ColorTools::FullColor[0] * 0.5f, ColorTools::FullColor[0] * 0.0f, ColorTools::FullColor[0] * 0.0f, ColorTools::Alpha[0]);
		glClear(GL_COLOR_BUFFER_BIT);

		vao_white.Bind();
		glDrawArrays(GL_TRIANGLES, 0, 6 * white.size());
		vao_white.Unbind();

		vao_black.Bind();
		glDrawArrays(GL_TRIANGLES, 0, 6 * black.size());
		vao_black.Unbind();

		shader1.UseShader();
		vao_selector.Bind();
		trans = glm::translate(trans, glm::vec3(0.f, .0f, .0f));
		glUniformMatrix4fv(uniform1, 1, GL_FALSE, glm::value_ptr(trans));
		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
			trans = glm::translate(trans, glm::vec3((float)1/boardSize, .0f, .0f));
			glUniformMatrix4fv(uniform1, 1, GL_FALSE, glm::value_ptr(trans));
		}
		if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
			trans = glm::translate(trans, glm::vec3(-(float)1 / boardSize, .0f, .0f));
			glUniformMatrix4fv(uniform1, 1, GL_FALSE, glm::value_ptr(trans));
		}
		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
			trans = glm::translate(trans, glm::vec3(.0f, -(float)1 / boardSize, .0f));
			glUniformMatrix4fv(uniform1, 1, GL_FALSE, glm::value_ptr(trans));
		}
		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
			trans = glm::translate(trans, glm::vec3(.0f, (float)1 / boardSize, .0f));
			glUniformMatrix4fv(uniform1, 1, GL_FALSE, glm::value_ptr(trans));
		}
		delay(50);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		vao_selector.Unbind();

		glfwPollEvents();
		glfwSwapBuffers(window);
	}
	Destroy();

	return EXIT_SUCCESS;
}
