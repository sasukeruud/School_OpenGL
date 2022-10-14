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

void VertexBuffer::SetData(const void* verticies, GLsizeiptr size) {
	int32_t bufferData = 0;

	glGenBuffers(1, &VertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, VertexBufferID);

	glBufferData(GL_ARRAY_BUFFER, size, verticies, GL_STATIC_DRAW);
	glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &bufferData);

	if (bufferData == 0) std::cout << "ERROR:: NO DATA IN BUFFER" << std::endl;
}

void VertexBuffer::Bind() const {
	glBindBuffer(GL_ARRAY_BUFFER, VertexBufferID);
}

void VertexBuffer::Unbind() const {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::BufferSubData(GLintptr offset, GLsizeiptr size, const void* data) const {
	glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
}

