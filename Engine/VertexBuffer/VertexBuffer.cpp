//Standard libraries
#include <iostream>

//Engine libraries
#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(GLsizei size) {
	glGenBuffers(size, &VertexBufferID);
}

VertexBuffer::VertexBuffer(const void* vertices,GLsizei size) {
	glGenBuffers(size, &VertexBufferID);
}

VertexBuffer::~VertexBuffer() {}

void VertexBuffer::Bind() const {
	glBindBuffer(GL_ARRAY_BUFFER, VertexBufferID);
}

void VertexBuffer::Unbind() const {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::BufferSubData(GLintptr offset, GLsizeiptr size, const void* data) const {
	glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
}

