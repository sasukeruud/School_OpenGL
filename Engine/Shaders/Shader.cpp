#include "Shader.h"

Shader::Shader(const std::string& vertexSrc, const std::string& fragmentSrc) {
	VertexShader = glCreateShader(GL_VERTEX_SHADER);
	FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	ShaderProgram = glCreateProgram();

	CompileShader(VertexShader, vertexSrc);
	CompileShader(FragmentShader, fragmentSrc);
}

Shader::~Shader() {}

void Shader::CompileShader(GLuint shader, const std::string& shaderSrc) {
	const GLchar* ss = shaderSrc.c_str();
	int success;
	char infoLog[512];

	glShaderSource(shader, 1, &ss, NULL);
	glCompileShader(shader);

	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::"<< shader <<"::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
}

void Shader::Bind() const {
	int success;
	char infoLog[512];

	glAttachShader(ShaderProgram, VertexShader);
	glAttachShader(ShaderProgram, FragmentShader);
	glLinkProgram(ShaderProgram);

	glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(ShaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::LINKING::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	Destory();
}

void Shader::UseShader() const {
	glUseProgram(ShaderProgram);
}

void Shader::Unbind() const {

}

void Shader::UploadUniformFloat2(const std::string& name, const glm::vec2& vector) {

}

void Shader::Destory() const {
	glDeleteShader(VertexShader);
	glDeleteShader(FragmentShader);
}