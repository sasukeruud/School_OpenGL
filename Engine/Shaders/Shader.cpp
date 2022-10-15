#include "Shader.h"

Shader::Shader(const std::string& vertexSrc, const std::string& fragmentSrc) {
	VertexShader = glCreateShader(GL_VERTEX_SHADER);
	FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	ShaderProgram = glCreateProgram();

	CompileShader(VertexShader, vertexSrc);
	CompileShader(FragmentShader, fragmentSrc);
}

Shader::Shader(const char* vertexPath, const char* fragmentPath) {
	VertexShader = glCreateShader(GL_VERTEX_SHADER);
	FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	ShaderProgram = glCreateProgram();

	std::string vertexCode, fragmentCode;
	std::ifstream vertexFile, fragmentFile;

	vertexFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fragmentFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try {
		//Open file
		vertexFile.open(vertexPath);
		fragmentFile.open(fragmentPath);
		std::stringstream vertexStream, fragmentStream;
		//Read file's buffer contents into streams
		vertexStream << vertexFile.rdbuf();
		fragmentStream << fragmentFile.rdbuf();
		//Close file handlers
		vertexFile.close();
		fragmentFile.close();
		//convert stream into string
		vertexCode = vertexStream.str();
		fragmentCode = fragmentStream.str();
	}
	catch (std::ifstream::failure e) {
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}

	CompileShader(VertexShader, vertexCode);
	CompileShader(FragmentShader, fragmentCode);
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

GLint Shader::UniformLocation(const GLchar* uniformName) {
	auto success = glGetUniformLocation(ShaderProgram, uniformName);
	if (success == -1) {
		std::cout << "ERROR: could not find location of uniform." << std::endl;
		return success;
	}
	else return success;
}

void Shader::SetUniform4f(GLint location, float v1, float v2, float v3, float v4) {
	glUniform4f(location, v1, v2, v3, v4);
}

void Shader::Destory() const {
	glDeleteShader(VertexShader);
	glDeleteShader(FragmentShader);
}