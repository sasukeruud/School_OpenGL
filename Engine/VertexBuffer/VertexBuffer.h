#pragma once

//Standard libraries
#include <iostream>
#include <vector>
//External libraries
#include <glad/glad.h>
//Engine libraries
#include "ShadersDataTypes.h"
#include "GeometricTools.h"

class VertexBuffer
{
private:
	GLuint VertexBufferID;

public:
	/*
	Default constructor. just a placeholder
	*/
	VertexBuffer() = default;

	/*
	Constructor. It initializes with a data buffer and the size of it.
	Generets the VBO
	size		: How many buffers to be created
	*/
	VertexBuffer(GLsizei size);

	/*
	Constructor. It initializes with a data buffer and the size of it.
	Generets the VBO
	verticies	: Data that will be copied onto the buffer
	size		: How many buffers to be created
	*/
	VertexBuffer(const void* vertices, GLsizei size);

	//Deconstructor
	~VertexBuffer();
	
	/*
	Sets data for the vbo
	verticies	: Data that will be copied onto the buffer
	target		: Spesify what type of buffer object to use. Normaly GL_ARRAY_BUFFER or GL_ELEMENT_ARRAY_BUFFER
	*/
	void SetData(const void* verticies, GLenum target);

	/*
	Binds vbo to vao
	index	: index number of vertex attribute
	size	: How many components per vertex
	*/
	void Bind(GLuint index, GLint size) const;

	// Unbind what is bound to the buffer, if no vbo is bound it will be set to 0
	void Unbind() const;

	// Fill out a specific segment of the buffer given by an offset and a size.
	void BufferSubData(GLintptr offset, GLsizeiptr size, const void* data) const;

};