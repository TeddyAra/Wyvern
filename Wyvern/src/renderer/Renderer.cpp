#include "Renderer.h"

#include <iostream>

const unsigned int indices[] = {
	 0,  2,  3,
	 0,  3,  1,
	 
	 4,  6,  7,
	 4,  7,  5,
	 
	 8, 10, 11,
	 8, 11,  9,

	12, 14, 15,
	12, 15, 13,

	16, 18, 19,
	16, 19, 17,

	20, 22, 23,
	20, 23, 21
};

const float vertices[] = {
	// Front face
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  1.0f,

	// Back face
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,
	-0.5f,  0.5f,  0.5f,  1.0f,  1.0f,
						  		 
	// Top face		  		 
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  1.0f,

	// Bottom face
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  1.0f,

	// Left face
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,
	-0.5f,  0.5f, -0.5f,  1.0f,  1.0f,

	// Right face
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  1.0f
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
	buffer->addLayout(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	buffer->addLayout(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

	framebuffer = std::make_unique<Framebuffer>(size, size);

	shader = std::make_unique<Shader>(shaderPath);
}

Renderer::~Renderer() {

}

void Renderer::render() {
	// Bind everything
	shader->bind();
	buffer->bind();
	framebuffer->bind();
	glEnable(GL_DEPTH_TEST);

	// Set viewport
	glViewport(0, 0, texSize.x, texSize.y);

	// Set view matrix
	GLuint viewLoc = glGetUniformLocation(shader->getID(), "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(world->getCamera()->getViewMatrix()));
	
	// Set projection matrix
	GLuint projectionLoc = glGetUniformLocation(shader->getID(), "projection");
	glm::mat4 projection = world->getCamera()->getProjectionMatrix(glm::vec2(texSize.x, texSize.y));
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

	// Get objects
	std::vector<std::shared_ptr<Transform>> objects = world->getObjects();
	std::vector<std::shared_ptr<Transform>> selected = world->getSelected();
	std::vector<std::shared_ptr<Transform>> transform = world->getTransformTools();

	GLuint transformLoc = glGetUniformLocation(shader->getID(), "transform");
	glUniform1i(transformLoc, 0);

	GLuint modelLoc = glGetUniformLocation(shader->getID(), "model");

	for (std::shared_ptr<Transform> object : objects) {
		// Set model matrix
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(object->getModelMatrix()));

		// Draw object
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(unsigned int), GL_UNSIGNED_INT, 0);
	}

	if (selected.size() > 0) {
		glDisable(GL_DEPTH_TEST);

		for (int i = 0; i < transform.size(); i++) {
			// Set transform
			glUniform1i(transformLoc, i + 1);

			// Set model matrix
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(transform[i]->getModelMatrix()));

			// Draw object
			glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(unsigned int), GL_UNSIGNED_INT, 0);
		}
	}

	// Unbind everything
	buffer->unbind();
	shader->unbind();
	framebuffer->unbind();
}

GLuint Renderer::getTex() {
	return framebuffer->getTexture();
}

void Renderer::clear() {
	framebuffer->bind();
	glViewport(0, 0, texSize.x, texSize.y);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	framebuffer->unbind();
}

void Renderer::updateSize(int posX, int posY, int width, int height) {
	std::cout << "Setting size to " << width << ", " << height << std::endl;
	framebuffer->updateTextureSize(width, height);
	texSize = ImVec2(width, height);
	world->updateViewport(posX, posY, width, height);
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