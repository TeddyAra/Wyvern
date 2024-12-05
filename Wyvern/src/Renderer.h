#pragma once

#define GLEW_STATIC
#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

class Renderer {
public:
	Renderer(GLFWwindow* window);
	~Renderer();

	void render();
	GLuint getTex();
	void clear();
	void updateSize(int width, int height);
	ImVec2 getSize();

private:
	GLFWwindow* window;

	GLuint VAO; // Vertex array object
	GLuint VBO; // Vertex buffer object
	GLuint EBO; // Element buffer object

	GLuint FBO; // Frame buffer object
	GLuint RBO; // Render buffer object

	GLuint tex;

	GLuint shaderProgram;
	ImVec2 texSize;
};