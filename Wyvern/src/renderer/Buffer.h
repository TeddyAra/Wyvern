#pragma once

#include "Renderer.h"

class Buffer {
public:
	Buffer(const float* vertices, size_t vertexSize, const GLuint* indices, size_t indexSize);
	~Buffer();

	void bind();
	void unbind();

	void addLayout(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* offset);

private:
	GLuint VAO, VBO, EBO;
};