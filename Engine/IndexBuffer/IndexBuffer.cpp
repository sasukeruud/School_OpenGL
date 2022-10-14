#include <iostream>

#include <glad/glad.h>

#include "IndexBuffer.h"
#include "VertexBuffer.h"

IndexBuffer::IndexBuffer(GLuint* indices, GLsizei count) {
	Count = count;
	glGenBuffers(count, &IndexBufferID);
	Bind();
}

IndexBuffer::~IndexBuffer() {

}

void IndexBuffer::Bind() const {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBufferID);
}

void IndexBuffer::Unbind() const {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void IndexBuffer::SetData(const void* verticies, GLsizeiptr size) {
	int32_t bufferData = 0;

	glGenBuffers(1, &IndexBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBufferID);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, verticies, GL_STATIC_DRAW);
	glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &bufferData);

	if (bufferData == 0) std::cout << "ERROR:: NO DATA IN BUFFER" << std::endl;
}


