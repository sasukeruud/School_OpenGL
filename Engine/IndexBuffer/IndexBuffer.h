#ifndef INDEXBUFFER_H_
#define INDEXBUFFER_H_

#include <iostream>

#include <glad/glad.h>

#include "VertexBuffer.h"

class IndexBuffer{
private:
	GLuint IndexBufferID;
	GLuint Count;

public:
	// Constructor. It initializes with a data buffer and the size of it.
	// Note that the buffer will be bound on construction and that the.size is
	// given in number of elements, not bytes
	IndexBuffer(GLuint* indices, GLsizei count);
	IndexBuffer() = default;
	~IndexBuffer();

	/*
	Binds ebo to buffer
	*/
	virtual void Bind() const;

	/*
	Unbinds ebo from buffer
	*/
	virtual void Unbind() const;

	/*
	Sets data for the ebo
	verticies	: Data that will be copied onto the buffer
	*/
	virtual void SetData(const void* verticies, GLsizeiptr size);

	// Get the number of elements
	inline GLuint GetCount() const { return Count; }

};
#endif INDEXBUFFER_H_