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
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> verticies_color;
	std::vector<glm::uvec3> indices;
	GeometricTools::GenGrid<std::vector<glm::vec3>, std::vector<glm::uvec3>>(5, vertices, indices);
	//GeometricTools::GenColorGrid<std::vector<glm::vec3>, std::vector<glm::uvec3>>(2, verticies_color, indices);

	auto vao = VertexArray();

	vao.Bind();
	auto vbo = VertexBuffer();
	auto vbo_color = VertexBuffer();

	vbo.SetData(glm::value_ptr(vertices[0]), (int)vertices.size() * sizeof(glm::vec3));
	vbo.Bind();
	vao.AddVertexBuffer(0, 3, vbo);
	vbo.Unbind();
	
	glm::vec3 white = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec3 black = glm::vec3(0.0f, 0.0f, 0.0f);
	std::vector<glm::vec3> colors;
	colors.push_back(white);
	colors.push_back(black);
	int change = 0;

	for (int i = 0; i < vertices.size(); i++)
	{
		if (i == 0 || i == 1 || i == 10)change = 0;
		else change = 1;
		verticies_color.push_back(colors[change]);
	}

	for (size_t i = 0; i < indices.size(); i++)
	{
		std::cout << indices[i].x << " " << indices[i].y << " " << indices[i].z << std::endl;
	}
	std::cout << "============" << std::endl;

	for (size_t i = 0; i < vertices.size(); i++)
	{
		std::cout << vertices[i].x << " " << vertices[i].y << " " << vertices[i].z << std::endl;
	}

	std::cout << "============" << std::endl;
	for (size_t i = 0; i < verticies_color.size(); i++)
	{
		std::cout << verticies_color[i].x << " " << verticies_color[i].y << " " << verticies_color[i].z << std::endl;
	}

	vbo_color.SetData(glm::value_ptr(verticies_color[0]), (int)verticies_color.size() * sizeof(glm::vec3));
	vbo_color.Bind();
	vao.AddVertexBuffer(1, 3, vbo_color);

	auto ibo = IndexBuffer();
	ibo.SetData(glm::value_ptr(indices[0]), (int)indices.size() * sizeof(glm::uvec3));
	ibo.Bind();

	const std::string& vertexShaderSrc = R"(
	#version 460

	layout (location = 0) in vec3 pos;
	layout (location = 1) in vec3 color;

	//flat removes inteporlotian
	flat out vec3 ourColor; 

	void main()
	{
		gl_Position = vec4(pos,1.0);
		ourColor = vec3(color.x,color.y,color.z);
	}
)";

	const std::string& fragmentShaderSrc = R"(
	#version 460 core
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
		WireframeMode();

		glClearColor(ColorTools::FullColor[0] * 0.5f, ColorTools::FullColor[0] * 0.0f, ColorTools::FullColor[0] * 0.0f, ColorTools::Alpha[0]);
		glClear(GL_COLOR_BUFFER_BIT);

		vao.Bind();
		//glDrawElements(GL_LINES, (GLsizei)indices.size() * 4, GL_UNSIGNED_INT, NULL);
		glDrawElements(GL_TRIANGLES, (GLsizei)indices.size() * 3, GL_UNSIGNED_INT, NULL);



		glfwPollEvents();
		glfwSwapBuffers(window);
	}
	Destroy();

	return EXIT_SUCCESS;
}
