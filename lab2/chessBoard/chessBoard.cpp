#include <iostream>

#include "chessBoard.h"

#define GLM_ENABLE_EXPERIMENTAL

void chessBoard::processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) std::cout << "Right" << std::endl;
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) std::cout << "Down" << std::endl;
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) std::cout << "Up" << std::endl;
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) std::cout << "Left" << std::endl;
}

unsigned int chessBoard::Run() {
	int boardSize = 8;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> verticies_color;
	std::vector<glm::uvec3> indices;
	std::vector<glm::uvec3> whiteIndicies;
	GeometricTools::GenGrid<std::vector<glm::vec3>, std::vector<glm::uvec3>>(boardSize, vertices, indices);
	//GeometricTools::GenColorGrid<std::vector<glm::vec3>, std::vector<glm::uvec3>>(2, verticies_color, indices);
	std::vector<glm::vec3> white;
	std::vector<glm::vec3> black;
	bool whiteStat = true;
	for (int i = 0; i < indices.size() - 1; i++)
	{
		if (whiteStat) {
			white.push_back(glm::vec3(vertices[indices[i].x].x, vertices[indices[i].x].y, vertices[indices[i].x].z));
			white.push_back(glm::vec3(vertices[indices[i].y].x, vertices[indices[i].y].y, vertices[indices[i].y].z));
			white.push_back(glm::vec3(vertices[indices[i].z].x, vertices[indices[i].z].y, vertices[indices[i].z].z));
			

			white.push_back(glm::vec3(vertices[indices[i + 1].x].x, vertices[indices[i + 1].x].y, vertices[indices[i + 1].x].z));
			white.push_back(glm::vec3(vertices[indices[i + 1].y].x, vertices[indices[i + 1].y].y, vertices[indices[i + 1].y].z));
			white.push_back(glm::vec3(vertices[indices[i + 1].z].x, vertices[indices[i + 1].z].y, vertices[indices[i + 1].z].z));
			
			whiteStat = false;
			i++;
		}
		else {
			black.push_back(glm::vec3(vertices[indices[i].x].x, vertices[indices[i].x].y, vertices[indices[i].x].z));
			black.push_back(glm::vec3(vertices[indices[i].y].x, vertices[indices[i].y].y, vertices[indices[i].y].z));
			black.push_back(glm::vec3(vertices[indices[i].z].x, vertices[indices[i].z].y, vertices[indices[i].z].z));

			black.push_back(glm::vec3(vertices[indices[i + 1].x].x, vertices[indices[i + 1].x].y, vertices[indices[i + 1].x].z));
			black.push_back(glm::vec3(vertices[indices[i + 1].y].x, vertices[indices[i + 1].y].y, vertices[indices[i + 1].y].z));
			black.push_back(glm::vec3(vertices[indices[i + 1].z].x, vertices[indices[i + 1].z].y, vertices[indices[i + 1].z].z));
			
			whiteStat = true;
			i++;
		}
		if (vertices[indices[i].x].x == 1 - (float)1/boardSize) whiteStat = !whiteStat;
	}
	
	auto vao_white = VertexArray();
	auto vao_black = VertexArray();
	auto vao2 = VertexArray();

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
	

	vao2.Bind();
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
	vbo_square.SetData(squareCurosr, sizeof(squareCurosr));
	vbo_square.Bind();
	vao2.AddVertexBuffer(0, 3, vbo_square);

	auto vbo_square_color = VertexBuffer();
	vbo_square_color.Bind();
	vbo_square_color.SetData(GeometricTools::ColorSquare2D, sizeof(GeometricTools::ColorSquare2D));
	vbo_square_color.Bind();
	vao2.AddVertexBuffer(1,3,vbo_square_color);

	const std::string& vertexShaderSrc = R"(
	#version 420

	#define center vec4(-0.5,-0.5,0,0)
	
	layout (location = 0) in vec3 pos;
	layout (location = 1) in vec3 color;

	//flat removes inteporlotian
	flat out vec3 ourColor; 

	void main()
	{
		gl_Position = vec4(pos,1.0) + center;
		ourColor = vec3(color.x,color.y,color.z);
	}
)";

	const std::string& fragmentShaderSrc = R"(
	#version 420 core

	#define M_PI 3.14159265

	out vec4 FragColor;

	//flat removes inteporlotian
	flat in vec3 ourColor;

	void main()
	{
			FragColor = vec4(ourColor, 1.0);
	})";

	auto shader = Shader::Shader(vertexShaderSrc, fragmentShaderSrc);
	shader.Bind();
	shader.UseShader();
	

	while (!glfwWindowShouldClose(window)) {
		processInput(window);
		//WireframeMode();

		glClearColor(ColorTools::FullColor[0] * 0.5f, ColorTools::FullColor[0] * 0.0f, ColorTools::FullColor[0] * 0.0f, ColorTools::Alpha[0]);
		glClear(GL_COLOR_BUFFER_BIT);

		vao_white.Bind();
		glDrawArrays(GL_TRIANGLES, 0, 6 * white.size());
		vao_white.Unbind();

		vao_black.Bind();
		glDrawArrays(GL_TRIANGLES, 0, 6 * black.size());
		vao_black.Unbind();

		vao2.Bind();
		glDrawArrays(GL_TRIANGLES, 0, 6);
		vao2.Unbind();

		glfwPollEvents();
		glfwSwapBuffers(window);
	}
	Destroy();

	return EXIT_SUCCESS;
}
