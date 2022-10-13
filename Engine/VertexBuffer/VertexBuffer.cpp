//Standard libraries
#include <iostream>

//Engine libraries
#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(const void* verticies, GLsizei size) {
	glGenBuffers(size, &VertexBufferID);
}

VertexBuffer::~VertexBuffer() {}

void VertexBuffer::SetData(const void* verticies){
	int32_t bufferData = 0;

	glGenBuffers(1, &VertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, VertexBufferID);

	glBufferData(GL_ARRAY_BUFFER, sizeof(GeometricTools::UnitTriangle2D), verticies, GL_STATIC_DRAW);
	glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &bufferData);

	if (bufferData == 0) std::cout << "ERROR:: NO DATA IN BUFFER" << std::endl;
}

void VertexBuffer::Bind(GLuint index, GLint valuePoint) const {
	glEnableVertexAttribArray(index);
	glBindBuffer(GL_ARRAY_BUFFER, VertexBufferID);
	glVertexAttribPointer(	index,
							valuePoint,
							GL_FLOAT,
							GL_FALSE,
							sizeof(float) * 3,
							NULL);
}

void VertexBuffer::Unbind() const {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::BufferSubData(GLintptr offset, GLsizeiptr size, const void* data) const {}

