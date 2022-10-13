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

void VertexBuffer::SetData(const void* verticies, GLenum target){
	int32_t bufferData = 0;

	glGenBuffers(1, &VertexBufferID);
	glBindBuffer(target, VertexBufferID);

	glBufferData(target, sizeof(GeometricTools::UnitTriangle2D), verticies, GL_STATIC_DRAW);
	glGetBufferParameteriv(target, GL_BUFFER_SIZE, &bufferData);

	if (bufferData == 0) std::cout << "ERROR:: NO DATA IN BUFFER" << std::endl;
}

void VertexBuffer::Bind(GLuint index, GLint size) const {
	glEnableVertexAttribArray(index);
	glBindBuffer(GL_ARRAY_BUFFER, VertexBufferID);
	glVertexAttribPointer(	index,
							size,
							GL_FLOAT,
							GL_FALSE,
							sizeof(float) * 3,
							NULL);
}

void VertexBuffer::Unbind() const {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::BufferSubData(GLintptr offset, GLsizeiptr size, const void* data) const {}

