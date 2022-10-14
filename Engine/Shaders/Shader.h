#pragma once

//Stanard libraries
#include <iostream>
//External libraries
#include <glad/glad.h>
#include <glm/glm.hpp>

class Shader {
private:
	GLuint VertexShader;
	GLuint FragmentShader;
	GLuint ShaderProgram;

	/*
	Function to compile a shader.
	shader		: The shader that data will be bind to
	shaderSrc	: Source code for shader data
	*/
	void CompileShader(GLuint shader, const std::string& shaderSrc);

	/*
	Deletes vertex and fragment shader
	*/
	void Destory() const;

public:
	/*
	Constructor for Shader class.
	Default takes no parameter and don't generate any shader data
	*/
	Shader() = default;

	/*
	Constructor for Shader class.
	Settes variables and compile fragment shader and vertex shader
	vertexSrc	: Source code for vertex shader
	fragmentSrc	: Source code for fragment shader
	*/
	Shader(const std::string& vertexSrc, const std::string& fragmentSrc);

	/*
	Deconstructor
	*/
	~Shader();

	/*
	Function to link shader data to shader program
	*/
	virtual void Bind() const;

	/*
	Not implemented
	*/
	virtual void Unbind() const;

	/*
	Sets the shader program to be used
	*/
	virtual void UseShader() const;

	/*
	Not implemented
	*/
	virtual void UploadUniformFloat2(const std::string& name, const glm::vec2& vector);

	/*
	Function to get the location of a uniform from a shader
	uniformName: Global name of the uniform that is made in a shader
	*/
	virtual GLint UniformLocation(const GLchar* uniformName);

	/*
	Function to set data of an uniform
	location: Location of where to uniform is
	v1		: First value of the uniform
	v2		: Second value of the uniform
	v3		: Third value of the uniform
	v4		: Fourth value of the uniform
	*/
	virtual void SetUniform(GLint location, float v1, float v2, float v3, float v4);
};