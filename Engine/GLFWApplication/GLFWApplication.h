#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class GLFWApplication
{
private:
	const char* title;
	unsigned int width{ 640 };
	unsigned int height{ 480 };

protected:
	GLFWwindow* window;

	void processInput(GLFWwindow* window);

public:
	GLFWApplication() = default;
	//GLFWApplication(const char& name, const std::string& version) {
	//	char title = name;
	//};
	//~GLFWApplication();

	//Function to generate arguments for the console of the application
	virtual unsigned int ParseArguments(int argc, char** argv);

	//Function to initalize glfw and glad for use
	virtual unsigned Init(const char* title);
	
	//Default run funciton, will run a black screen with nothing
	virtual unsigned Run();

	//Funtion to terminate glfw memory locations
	virtual unsigned int Destroy();
};
