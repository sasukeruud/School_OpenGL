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
	TODO: add binding option
	verticies	: Data that will be copied onto the buffer
	size		: How many buffers to be created
	*/
	VertexBuffer(const void* vertices, GLsizei size);

	//Deconstructor
	~VertexBuffer();
	
	/*
	Sets data for the vbo
	verticies	: Data that will be copied onto the buffer
	size		: Size of the copied data
	*/
	template<class T> void SetData(T* verticies, int size) {
		int32_t bufferData = 0;

		glGenBuffers(1, &VertexBufferID);
		glBindBuffer(GL_ARRAY_BUFFER, VertexBufferID);

		glBufferData(GL_ARRAY_BUFFER, size, verticies, GL_DYNAMIC_DRAW);
		glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &bufferData);

		if (bufferData == 0) std::cout << "ERROR:: NO DATA IN BUFFER" << std::endl;
	}

	/*
	Binds vbo
	*/
	void Bind() const;

	/*
	Unbind what is bound to the buffer, if no vbo is bound it will be set to 0
	*/
	void Unbind() const;

	// Fill out a specific segment of the buffer given by an offset and a size.
	//TODO: finish, for changing subdata
	void BufferSubData(GLintptr offset, GLsizeiptr size, const void* data) const;

};