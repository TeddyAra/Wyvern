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
#include "Texture.h"
#include "Skybox.h"

struct Line {
	glm::vec3 posA;
	glm::vec3 posB;
	glm::vec4 colour;

	Line(glm::vec3 posA, glm::vec3 posB, glm::vec4 colour) {
		this->posA = posA;
		this->posB = posB;
		this->colour = colour;
	}
};

class Renderer {
public:
	Renderer(GLFWwindow* window, std::shared_ptr<World> world, std::string& shaderPath, std::string& transformShaderPath);
	~Renderer();

	void addTexture(const char* name, const char* path);

	void render();
	GLuint getFramebufferTexture();
	void clear();
	void updateSize(int posX, int posY, int width, int height);
	ImVec2 getSize();

	void addSkybox(std::vector<std::string> faces);

	void addLine(glm::vec3 posA, glm::vec3 posB, glm::vec4 colour = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
	void clearLines();

private:
	GLFWwindow* window;
	std::shared_ptr<World> world;
	std::vector<Line> lines;
	std::vector<std::shared_ptr<Texture>> textures;
	std::unique_ptr<Skybox> skybox;

	std::unique_ptr<Buffer> mainBuffer;
	std::unique_ptr<Shader> mainShader;

	std::unique_ptr<Buffer> transformBuffer;
	std::unique_ptr<Shader> transformShader;
	std::vector<unsigned int> transformIndices;
	std::vector<glm::vec3> transformVertices;

	std::unique_ptr<Framebuffer> framebuffer;

	ImVec2 texSize;

	void drawLines();
	GLuint getTexture(const char* name);

	void setupOpenGLState();
};