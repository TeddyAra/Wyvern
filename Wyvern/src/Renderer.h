#pragma once

#define GLEW_STATIC
#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include <string>

#include "World.h"
#include "Shader.h"
#include "Buffer.h"
#include "Framebuffer.h"

class Renderer {
public:
	Renderer(GLFWwindow* window, std::shared_ptr<World> world, std::string& shaderPath);
	~Renderer();

	void render();
	GLuint getTex();
	void clear();
	void updateSize(int width, int height);
	ImVec2 getSize();

private:
	GLFWwindow* window;
	std::shared_ptr<World> world;

	std::unique_ptr<Shader> shader;
	std::unique_ptr<Buffer> buffer;
	std::unique_ptr<Framebuffer> framebuffer;

	//GLuint VAO; // Vertex array object
	//GLuint VBO; // Vertex buffer object
	//GLuint EBO; // Element buffer object

	//GLuint FBO; // Frame buffer object
	//GLuint RBO; // Render buffer object

	//GLuint tex;

	ImVec2 texSize;

	void setupOpenGLState();
};