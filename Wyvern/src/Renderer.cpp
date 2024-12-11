#include "Renderer.h"

#include <iostream>

const unsigned int indices[] = {
	0, 2, 3,
	0, 3, 1
};

const float vertices[] = {
	-0.25f, -0.25f, 0.0f, 0.0f, 0.0f,
	 0.25f, -0.25f, 0.0f, 1.0f, 0.0f,
	-0.25f,  0.25f, 0.0f, 0.0f, 1.0f,
	 0.25f,  0.25f, 0.0f, 1.0f, 1.0f
};

void GLAPIENTRY messageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
	std::cerr << "OpenGL Debug Message: " << message << std::endl;
}

Renderer::Renderer(GLFWwindow* window, std::shared_ptr<World> world, std::string& shaderPath)
	: window(window), world(world), shader(nullptr), buffer(nullptr)
{
	const int size = 64;

	setupOpenGLState();

	buffer = std::make_unique<Buffer>(vertices, sizeof(vertices), indices, sizeof(indices));
	framebuffer = std::make_unique<Framebuffer>(size, size);

	// index, size, type, normalized, stride, pointer
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//const char* vertexShaderSource = R"(
	//	#version 330
	//	layout(location = 0) in vec3 aPos;
	//	layout(location = 1) in vec2 aTexCoord;

	//	out vec2 TexCoord;

	//	uniform mat4 view;
	//	uniform mat4 projection;

	//	void main() {
	//		gl_Position = projection * view * vec4(aPos, 1.0f);
	//		TexCoord = aTexCoord;
	//	}
	//)";

	//const char* fragmentShaderSource = R"(
	//	#version 330
	//	in vec2 TexCoord;
	//	
	//	out vec4 FragColor;

	//	void main() {
	//		FragColor = vec4(0.0f, 1.0f, 0.0f, 1.0f); //vec4(TexCoord, 0.0f, 1.0f);
	//	}
	//)";

	shader = std::make_unique<Shader>(shaderPath);
}

Renderer::~Renderer() {

}

void Renderer::render() {
	shader->bind();
	buffer->bind();

	framebuffer->bind();
	glViewport(0, 0, texSize.x, texSize.y);

	int windowWidth, windowHeight;
	glfwGetWindowSize(window, &windowWidth, &windowHeight);

	GLuint viewLoc = glGetUniformLocation(shader->getID(), "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(world->getCamera()->getViewMatrix()));

	GLuint projectionLoc = glGetUniformLocation(shader->getID(), "projection");
	glm::mat4 projection = glm::perspective(glm::radians(world->getCamera()->getFov()), (float)windowWidth / (float)windowHeight, 0.1f, 100.0f);
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	buffer->unbind();
	shader->unbind();
	framebuffer->unbind();
	glViewport(0, 0, windowWidth, windowHeight);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

GLuint Renderer::getTex() {
	return framebuffer->getTexture();
}

void Renderer::clear() {
	framebuffer->bind();
	glViewport(0, 0, texSize.x, texSize.y);
	glClearColor(1.0f, 0.0f, 0.0f, 0.5f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	framebuffer->unbind();
}

void Renderer::updateSize(int width, int height) { 
	std::cout << "Setting size to " << width << ", " << height << std::endl;
	framebuffer->updateTextureSize(width, height);
	texSize = ImVec2(width, height);
}

ImVec2 Renderer::getSize() {
	return texSize;
}

void Renderer::setupOpenGLState() {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glEnable(GL_TEXTURE_2D);

	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageCallback(messageCallback, 0);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, GL_FALSE);
}