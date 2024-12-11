#pragma once

#define GLEW_STATIC
#include "GL/glew.h"
#include "GLFW/glfw3.h"

class Buffer {
public:
	Buffer(const float* vertices, size_t vertexSize, const GLuint* indices, size_t indexSize);
	~Buffer();

	void bind();
	void unbind();

private:
	GLuint VAO, VBO, EBO;

	void setupVertexAttributes();
};