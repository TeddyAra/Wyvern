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
#include <memory>
#include <vector>

class World;
class Shader;
class Buffer;
class Framebuffer;
class Texture;
class Skybox;

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

	void addSkybox(std::vector<std::string> faces, std::string& skyboxShaderPath);

	struct IndicesInfo {
		int moveStart;
		int moveCount;
		int scaleStart;
		int scaleCount;
		int rotateStart;
		int rotateCount;
	};

private:
	GLFWwindow* window;
	std::shared_ptr<World> world;
	std::vector<std::shared_ptr<Texture>> textures;
	std::unique_ptr<Skybox> skybox;

	std::unique_ptr<Buffer> mainBuffer;
	std::unique_ptr<Shader> mainShader;

	std::unique_ptr<Buffer> transformBuffer;
	std::unique_ptr<Shader> transformShader;
	std::vector<unsigned int> transformIndices;
	std::vector<glm::vec3> transformVertices;

	std::unique_ptr<Buffer> skyboxBuffer;
	std::unique_ptr<Shader> skyboxShader;

	std::unique_ptr<Framebuffer> framebuffer;

	ImVec2 texSize;
	IndicesInfo info;

	void drawLines();
	void drawSkybox();
	GLuint getTexture(const char* name);

	void fillTransformVectors(std::vector<unsigned int>& indices, std::vector<glm::vec3>& vertices, Renderer::IndicesInfo& info);
	void fillMoveVectors(std::vector<unsigned int>& indices, std::vector<glm::vec3>& vertices);
	void fillScaleVectors(std::vector<unsigned int>& indices, std::vector<glm::vec3>& vertices);
	void fillRotateVectors(std::vector<unsigned int>& indices, std::vector<glm::vec3>& vertices);

	void setupOpenGLState();
};