#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "ColorTools.h"
#include "GeometricTools.h"
#include "GLFWApplication.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "RenderCommands.h"

class lab4 : public GLFWApplication {

public:
	unsigned int Run() override;

	void processInput(GLFWwindow* window) override;
};