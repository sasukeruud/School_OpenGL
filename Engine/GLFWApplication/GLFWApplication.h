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

public:
	GLFWApplication() = default;
	//GLFWApplication(const char& name, const std::string& version) {
	//	char title = name;
	//};
	//~GLFWApplication();

	

	//Argument parsing
	virtual unsigned int ParseArguments(int argc, char** argv); // Virtual function with default behavior.
	// Initialization
	virtual unsigned Init(const char* title); // Virtual function with defaut behavior
	// Run function
	virtual unsigned Run();
	//Destroy function
	virtual unsigned int Destroy();
	//....
};
