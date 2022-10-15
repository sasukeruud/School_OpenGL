#pragma once

//Standard C++ libraries
#include <iostream>
#include <vector>
//External libraries
#include <glad/glad.h>
//Project libraries
#include "VertexBuffer.h"
#include "IndexBuffer.h"

class VertexArray {
private:
	GLuint VAO;

public:
	/*
	Constructor for VAO. Generates a VAO
	*/
	VertexArray();
	
	/*
	Destructor
	*/
	~VertexArray();

	/*
	Bind the VAO.
	*/
	void Bind() const;

	/*
	Unbind the VAO
	*/
	void Unbind() const;

	// Add vertex buffer. This method utilizes the BufferLayout internal to 
	// the vertex buffer to set up the vertex attributes. Notice that 
	// this function opens for the definition of several vertex buffers.

	/*
	Binds vbo to vao
	index	: index number of vertex attribute
	size	: How many components per vertex
	*/
	void AddVertexBuffer(GLuint index, GLint size, const VertexBuffer& vertexBuffer);

	/*
	Binds vbo to vao
	index	: index number of vertex attribute
	size	: How many components per vertex
	*/
	void AddVertexBuffer(GLuint index, GLint size, const IndexBuffer& indexBuffer);
	// Set index buffer
	//void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer);

	//Get the index buffer
	//const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const { return IdxBuffer; }
};
