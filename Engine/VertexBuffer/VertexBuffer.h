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
	// Constructor. It initializes with a data buffer and the size of it.
	// Note that the buffer will be bound on construction.
	VertexBuffer() = default;
	VertexBuffer(const void* vertices, GLsizei size);
	~VertexBuffer();
	
	// Sets data for the vbo
	void SetData(const void* verticies);

	//Binds vbo to vao
	void Bind(GLuint index, GLint valuePoint) const;

	// Unbind what is bound to the buffer, if no vbo is bound it will be set to 0
	void Unbind() const;

	// Fill out a specific segment of the buffer given by an offset and a size.
	void BufferSubData(GLintptr offset, GLsizeiptr size, const void* data) const;

};