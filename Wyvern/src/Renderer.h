#pragma once

#define GLEW_STATIC
#include "GL/glew.h"
#include "GLFW/glfw3.h"

class Renderer {
public:
	Renderer(GLFWwindow* window);
	~Renderer();

	void render();

private:
	GLFWwindow* window;

	GLuint VAO;
	GLuint VBO;
	GLuint EBO;

	GLuint shaderProgram;
};