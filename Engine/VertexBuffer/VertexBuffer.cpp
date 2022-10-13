#include <iostream>
#include "VertexBuffer.h"
#include <glad/glad.h>

VertexBuffer::VertexBuffer(const void* verticies, GLsizei size) {
	glGenBuffers(size, &VertexBufferID);
	Bind(verticies);
	Unbind();
}

VertexBuffer::~VertexBuffer() {

}

template<class T> void VertexBuffer::Bind(T verticies) const{
	glBindBuffer(GL_ARRAY_BUFFER, VertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);
}

void VertexBuffer::Unbind() const {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::BufferSubData(GLintptr offset, GLsizeiptr size, const void* data) const {

}

