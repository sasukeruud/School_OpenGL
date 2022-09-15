#include <iostream>

class GLFWApplication
{
public:
	GLFWApplication(const std::string& name, const std::string& version);
	~GLFWApplication();

	//Argument parsing
	virtual unsigned int ParseArguments(int argc, char** argv); // Virtual function with default behavior.
	// Initialization 
	virtual unsigned Init(); // Virtual function with defaut behavior
	// Run function
	virtual unsigned Run() const = 0; // Pure virtual function, it must be redefined
	//....
	//....
};
