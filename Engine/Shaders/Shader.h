#pragma once

#include <iostream>
#include <glad/glad.h>

#include <glm/glm.hpp>

class Shader {
private:
	GLuint VertexShader;
	GLuint FragmentShader;
	GLuint ShaderProgram;

	void CompileShader(GLuint shader, const std::string& shaderSrc);
	void Destory() const;

public:
	Shader() = default;
	Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
	//~Shader();

	void Bind() const;
	void Unbind() const;
	void UseShader() const;
	void UploadUniformFloat2(const std::string& name, const glm::vec2& vector);

};