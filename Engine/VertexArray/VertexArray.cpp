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

template<class T> void VertexArray::AddVertexBuffer(const VertexBuffer& vertexBuffer, T verticies) {
	auto vbo = VertexBuffer::VertexBuffer(verticies, 1);
	vbo.Bind(verticies);

	glVertexAttribPointer(0,
		3,
		GL_FLOAT,
		GL_FALSE,
		3 * sizeof(float),
		(void*)0);
	/*
	glVertexAttribPointer(	vertexBuffer.GetAttributes().data()->Offset, 
							vertexBuffer.GetAttributes().data()->Size,
							ShaderDataTypeToOpenGLBaseType(vertexBuffer.GetAttributes().data()->Type),
							vertexBuffer.GetAttributes().data()->Normalized,
							vertexBuffer.GetStride(), 
							NULL);*/

	glEnableVertexAttribArray(0);
}
