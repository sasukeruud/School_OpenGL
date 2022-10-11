#include <iostream>
#include <tclap/CmdLine.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "GLFWApplication.h"

GLFWwindow* window;

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}


unsigned int GLFWApplication::ParseArguments(int argc, char **argv) {
	try {
		TCLAP::CmdLine cmd("Command descritption", ' ', "0.9");

		//New command line agruments for executebl
		TCLAP::ValueArg<std::string> widthArg("w", "width=", "Width of window", false, "600", "string"); //Argument to change width of window
		TCLAP::ValueArg<std::string> heightArg("H", "height=", "height of window", false, "600", "string");	//Argument to change height of window
		TCLAP::SwitchArg triangleArg("t", "triangle", "Draw a triangle", cmd, false);
		TCLAP::SwitchArg squareArg("s", "square", "Draw a square", cmd, false);
		TCLAP::SwitchArg consoleArg("c", "console", "console", cmd, false);

		cmd.add(widthArg);
		cmd.add(heightArg);

		cmd.parse(argc, argv);

		bool console{ consoleArg.getValue() };

		if (consoleArg) {
			std::cout << "Hello OpenGL: Console" << std::endl;
		}
		if (widthArg.isSet()) {
			width = std::stoi(widthArg.getValue());
		}
		if (heightArg.isSet()) {
			height = std::stoi(heightArg.getValue());
		}
	}
	catch (TCLAP::ArgException& e) {
		std::cout << "Error: " << e.error() << " for arg: " << e.argId() << std::endl;
	}

	return EXIT_SUCCESS;
}

unsigned int GLFWApplication::Init() {
	try {
		//Initialize library 
		if (!glfwInit()) {
			return EXIT_FAILURE;
		}

		//Which versions of openGl that can be used to run the software
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);

		// Create a windowed mode and its OpenGL context
		window = glfwCreateWindow(width, height, "title", NULL, NULL);
		if (!window) {
			glfwTerminate();
			return EXIT_FAILURE;
		}
		glfwSetKeyCallback(window, key_callback);
		glfwMakeContextCurrent(window);

		//Glad loader
		if (!gladLoadGL) {
			std::cout << "Glad did not load properly" << std::endl;
			glfwDestroyWindow(window);	//Destroys window
			glfwTerminate();
			return EXIT_FAILURE;
		}
		gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	}
	catch (std::exception& e) {
		std::cout << "ERROR: " << e.what() << std::endl;
	}

	return EXIT_SUCCESS;
}

unsigned int GLFWApplication::Run() {
	try {
		while (!glfwWindowShouldClose(window)) {
			glClear(GL_COLOR_BUFFER_BIT);

			glfwSwapBuffers(window);

			glfwPollEvents();
		}
	}
	catch (std::exception& e) {
		std::cout << "ERROR: " << e.what() << std::endl;
	}
	glfwDestroyWindow(window);	//Destroys window
	glfwTerminate();

	return EXIT_SUCCESS;
}

unsigned int GLFWApplication::Destroy() {
	glfwDestroyWindow(window);	//Destroys window
	glfwTerminate();

	return EXIT_SUCCESS;
}