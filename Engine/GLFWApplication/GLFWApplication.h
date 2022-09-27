#include <iostream>

namespace GLFWApplication {
	class GLFWApplication
	{
	
	public:
		//GLFWApplication(const std::string& name, const std::string& version);
		//~GLFWApplication();

		//Argument parsing
		virtual unsigned int ParseArguments(int argc, char** argv); // Virtual function with default behavior.
		// Initialization
		virtual unsigned Init(); // Virtual function with defaut behavior
		// Run function
		virtual unsigned Run();
		//Destroy function
		virtual unsigned int Destroy();
		//....
	};
}