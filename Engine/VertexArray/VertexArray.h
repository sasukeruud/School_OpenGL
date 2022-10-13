#pragma once

//Standard C++ libraries
#include <iostream>
#include <vector>

//External libraries
#include <glad/glad.h>

//Project libraries
#include "VertexBuffer.h"

class VertexArray {
private:
	GLuint VAO;

public:
	// Constructor & Destructor
	VertexArray();
	~VertexArray();

	// Bind vertex array
	void Bind() const;
	// Unbind vertex array
	void Unbind() const;

	// Add vertex buffer. This method utilizes the BufferLayout internal to 
	// the vertex buffer to set up the vertex attributes. Notice that 
	// this function opens for the definition of several vertex buffers.
	template<class T> void AddVertexBuffer(const VertexBuffer& vertexBuffer, T verticies);
	// Set index buffer
	//void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer);

	//Get the index buffer
	//const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const { return IdxBuffer; }
};
