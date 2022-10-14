#include "VertexArray.h"

VertexArray::VertexArray() {
	glGenVertexArrays(1, &VAO);
	Unbind();
}

VertexArray::~VertexArray() {

}

void VertexArray::Bind() const {
	glBindVertexArray(VAO);
}

void VertexArray::Unbind() const {
	glBindVertexArray(0);
}

void VertexArray::AddVertexBuffer(GLuint index, GLint size, const VertexBuffer& vertexBuffer) {
	glVertexAttribPointer(	index,
							size,
							GL_FLOAT,
							GL_FALSE,
							3 * sizeof(float),
							NULL);

	glEnableVertexAttribArray(0);
}

void VertexArray::AddVertexBuffer(GLuint index, GLint size, const IndexBuffer& indexBuffer) {
	glVertexAttribPointer(index,
		size,
		GL_FLOAT,
		GL_FALSE,
		3 * sizeof(float),
		NULL);

	glEnableVertexAttribArray(0);
}