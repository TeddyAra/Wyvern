#include "Renderer.h"

#include <iostream>

#include "Debug.h"

#include "World.h"
#include "Shader.h"
#include "Buffer.h"
#include "Framebuffer.h"
#include "Texture.h"
#include "Skybox.h"

const unsigned int mainIndices[] = {
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

const float mainVertices[] = {
/*
*	Vertex---------------  UV------------  Normal---------------
*	x      y      z        u      v        x      y      z
*/

	// Front face
	-0.5f, -0.5f, -0.5f,    0.0f,  0.0f,    0.0f,  0.0f, -1.0f,
	 0.5f, -0.5f, -0.5f,    1.0f,  0.0f,    0.0f,  0.0f, -1.0f,
	-0.5f,  0.5f, -0.5f,    0.0f,  1.0f,    0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,    1.0f,  1.0f,    0.0f,  0.0f, -1.0f,
						    			    
	// Back face		    			    
	 0.5f, -0.5f,  0.5f,    0.0f,  0.0f,    0.0f,  0.0f,  1.0f,
	-0.5f, -0.5f,  0.5f,    1.0f,  0.0f,    0.0f,  0.0f,  1.0f,
	 0.5f,  0.5f,  0.5f,    0.0f,  1.0f,    0.0f,  0.0f,  1.0f,
	-0.5f,  0.5f,  0.5f,    1.0f,  1.0f,    0.0f,  0.0f,  1.0f,
						    		 	    
	// Top face		  		   			    
	-0.5f,  0.5f, -0.5f,    0.0f,  0.0f,    0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,    1.0f,  0.0f,    0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,    0.0f,  1.0f,    0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,    1.0f,  1.0f,    0.0f,  1.0f,  0.0f,
						    			    
	// Bottom face		    			    
	-0.5f, -0.5f, -0.5f,    0.0f,  0.0f,    0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,    1.0f,  0.0f,    0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,    0.0f,  1.0f,    0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,    1.0f,  1.0f,    0.0f, -1.0f,  0.0f,
						    			    
	// Left face		    			    
	-0.5f, -0.5f,  0.5f,    0.0f,  0.0f, -  1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,    1.0f,  0.0f, -  1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,    0.0f,  1.0f, -  1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,    1.0f,  1.0f, -  1.0f,  0.0f,  0.0f,
						    			    
	// Right face		    			    
	 0.5f, -0.5f, -0.5f,    0.0f,  0.0f,    1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,    1.0f,  0.0f,    1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,    0.0f,  1.0f,    1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,    1.0f,  1.0f,    1.0f,  0.0f,  0.0f
};

void Renderer::fillTransformVectors(std::vector<unsigned int>& indices, std::vector<glm::vec3>& vertices, Renderer::IndicesInfo& info) {
	info.moveStart = 0;
	fillMoveVectors(indices, vertices);
	info.moveCount = indices.size();

	info.scaleStart = info.moveCount;
	fillScaleVectors(indices, vertices);
	info.scaleCount = indices.size() - info.moveCount;

	info.rotateStart = info.moveCount + info.scaleCount;
	fillRotateVectors(indices, vertices);
	info.rotateCount = indices.size() - info.moveCount - info.scaleCount;
}

void Renderer::fillMoveVectors(std::vector<unsigned int>& indices, std::vector<glm::vec3>& vertices) {
	const int faceCount = 16;
	const float coneHeight = 0.2f;
	const float coneRadius = 1.0f;

	glm::vec3 axis(0.0f, 0.0f, 1.0f);

	vertices.push_back(glm::vec3(0.0f, 0.0f, -0.5f));
	vertices.push_back(glm::vec3(0.0f, 0.0f, 0.5f - coneHeight));
	vertices.push_back(glm::vec3(0.0f, 0.0f, 0.5f));

	for (float i = 0; i < 360; i += 360 / faceCount) {
		glm::vec3 vertex(0.0f, 0.5f, 0.0f);

		glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(i), axis);
		vertex = glm::vec3(rotationMatrix * glm::vec4(vertex, 0.0f));

		vertices.push_back(vertex - glm::vec3(0.0f, 0.0f, 0.5f));
		vertices.push_back(vertex + glm::vec3(0.0f, 0.0f, 0.5f - coneHeight));
		vertices.push_back(glm::normalize(vertex) * coneRadius + glm::vec3(0.0f, 0.0f, 0.5f - coneHeight));
	}

	if (vertices.size() < 12) {
		std::cerr << "Cylinder objects do not have enough faces" << std::endl;
		return;
	}

	for (int i = 6; i < vertices.size(); i += 3) {
		// Bottom
		indices.push_back(0);
		indices.push_back(i - 3);
		indices.push_back(i);

		// Side
		indices.push_back(i - 3);
		indices.push_back(i - 2);
		indices.push_back(i + 1);

		indices.push_back(i - 3);
		indices.push_back(i + 1);
		indices.push_back(i);

		// Cone bottom
		indices.push_back(1);
		indices.push_back(i - 1);
		indices.push_back(i + 2);

		// Cone top
		indices.push_back(i - 1);
		indices.push_back(2);
		indices.push_back(i + 2);
	}

	int max = vertices.size() - 3;

	// Bottom
	indices.push_back(0);
	indices.push_back(max);
	indices.push_back(3);

	// Side
	indices.push_back(max);
	indices.push_back(max + 1);
	indices.push_back(4);

	indices.push_back(max);
	indices.push_back(4);
	indices.push_back(3);

	// Cone bottom
	indices.push_back(1);
	indices.push_back(max + 2);
	indices.push_back(5);

	// Cone top
	indices.push_back(max + 2);
	indices.push_back(2);
	indices.push_back(5);
}

void Renderer::fillScaleVectors(std::vector<unsigned int>& indices, std::vector<glm::vec3>& vertices) {
	const int divisions = 2;
	std::vector<glm::vec3> sphereVertices;

	glm::vec3 directions[] = {
		{ -0.5f, -0.5f, -0.5f },
		{  1.0f,  0.0f,  0.0f },
		{  0.0f,  1.0f,  0.0f },

		{  0.5f, -0.5f, -0.5f },
		{  0.0f,  0.0f,  1.0f },
		{  0.0f,  1.0f,  0.0f },

		{  0.5f, -0.5f,  0.5f },
		{ -1.0f,  0.0f,  0.0f },
		{  0.0f,  1.0f,  0.0f },

		{ -0.5f, -0.5f,  0.5f },
		{  0.0f,  0.0f, -1.0f },
		{  0.0f,  1.0f,  0.0f },

		{ -0.5f,  0.5f, -0.5f },
		{  1.0f,  0.0f,  0.0f },
		{  0.0f,  0.0f,  1.0f },

		{ -0.5f, -0.5f,  0.5f },
		{  1.0f,  0.0f,  0.0f },
		{  0.0f,  0.0f, -1.0f }
	};

	for (int i = 0; i < sizeof(directions) / sizeof(directions[0]); i += 3) {
		for (float y = 0.0f; y <= 1.0f; y += 1.0f / (divisions + 1)) {
			for (float x = 0.0f; x <= 1.0f; x += 1.0f / (divisions + 1)) {
				glm::vec3 pos = directions[i] + directions[i + 1] * x + directions[i + 2] * y;
				sphereVertices.push_back(pos);

				if (x != 0.0f && y != 0.0f) {
					int topRight = vertices.size() + sphereVertices.size() - 1;
					int topLeft = topRight - 1;
					int bottomRight = topRight - divisions - 2;
					int bottomLeft = bottomRight - 1;

					indices.push_back(bottomLeft);
					indices.push_back(topLeft);
					indices.push_back(topRight);

					indices.push_back(bottomLeft);
					indices.push_back(topRight);
					indices.push_back(bottomRight);
				}
			}
		}
	}

	for (glm::vec3& vertex : sphereVertices) {
		vertex = glm::normalize(vertex) * 0.5f;
	}

	vertices.insert(vertices.end(), sphereVertices.begin(), sphereVertices.end());
}

void Renderer::fillRotateVectors(std::vector<unsigned int>& indices, std::vector<glm::vec3>& vertices) {

}

void GLAPIENTRY messageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
	std::cerr << "OpenGL Debug Message: " << message << std::endl;
}

Renderer::Renderer(GLFWwindow* window, std::shared_ptr<World> world, std::string& mainShaderPath, std::string& transformShaderPath)
	: window(window), world(world), skybox(nullptr),
	mainBuffer(nullptr), mainShader(nullptr),
	transformBuffer(nullptr), transformShader(nullptr)
{
	setupOpenGLState();

	fillTransformVectors(transformIndices, transformVertices, info);

	// Main buffer and shader
	mainBuffer = std::make_unique<Buffer>(mainVertices, sizeof(mainVertices), mainIndices, sizeof(mainIndices));
	mainBuffer->addLayout(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	mainBuffer->addLayout(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	mainBuffer->addLayout(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));

	mainShader = std::make_unique<Shader>(mainShaderPath);

	// Transform buffer and shader
	transformBuffer = std::make_unique<Buffer>(reinterpret_cast<const float*>(transformVertices.data()), transformVertices.size() * sizeof(glm::vec3), transformIndices.data(), transformIndices.size() * sizeof(unsigned int));
	transformBuffer->addLayout(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	transformShader = std::make_unique<Shader>(transformShaderPath);

	// Frame buffer
	const int size = 64;
	framebuffer = std::make_unique<Framebuffer>(size, size);
}

Renderer::~Renderer() {

}

void Renderer::addTexture(const char* name, const char* path) {
	std::shared_ptr<Texture> texture = std::make_shared<Texture>(name, path, GL_TEXTURE0 + textures.size());
	textures.push_back(texture);
}

void Renderer::render() {
	// Bind everything
	mainShader->bind();
	mainBuffer->bind();
	framebuffer->bind();

	// Set viewport
	glViewport(0, 0, texSize.x, texSize.y);

	if (skybox != nullptr) {
		drawSkybox();
		mainBuffer->bind();
		mainShader->bind();
	}

	// Set texture
	GLuint texture = getTexture("polyfoam");
	if (texture == 0) return;
	glBindTexture(GL_TEXTURE_2D, texture);

	// Get uniform locations
	GLuint sunDirLoc = glGetUniformLocation(mainShader->getID(), "sunDirection");
	GLuint sunStrLoc = glGetUniformLocation(mainShader->getID(), "sunStrength");
	GLuint ambLightLoc = glGetUniformLocation(mainShader->getID(), "ambientLight");
	GLuint ambStrLoc = glGetUniformLocation(mainShader->getID(), "ambientStrength");

	GLuint viewLoc = glGetUniformLocation(mainShader->getID(), "view");
	GLuint projectionLoc = glGetUniformLocation(mainShader->getID(), "projection");
	GLuint modelLoc = glGetUniformLocation(mainShader->getID(), "model");

	GLuint colourLoc = glGetUniformLocation(mainShader->getID(), "colour");
	GLuint scaleLoc = glGetUniformLocation(mainShader->getID(), "scale");
	GLuint gridLoc = glGetUniformLocation(mainShader->getID(), "grid");

	// Set uniforms
	glm::vec3 sunDirection = world->getSunDirection();
	glUniform3f(sunDirLoc, sunDirection.x, sunDirection.y, sunDirection.z);

	float sunStrength = world->getSunStrength();
	glUniform1f(sunStrLoc, sunStrength);

	glm::vec3 ambientLight = world->getAmbientLight();
	glUniform3f(ambLightLoc, ambientLight.r, ambientLight.g, ambientLight.b);

	float ambientStrength = world->getAmbientStrength();
	glUniform1f(ambStrLoc, ambientStrength);

	glm::mat4 view = world->getCamera()->getViewMatrix();
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	
	glm::mat4 projection = world->getCamera()->getProjectionMatrix(glm::vec2(texSize.x, texSize.y));
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

	// Get objects
	std::vector<std::shared_ptr<Transform>>& objects = world->getObjects();
	std::vector<std::shared_ptr<Transform>>& selected = world->getSelected();
	std::vector<std::shared_ptr<Transform>>& transform = world->getTransformTools();
	
	for (std::shared_ptr<Transform> object : objects) {
		if (!object->checkLayer(Physics::getLayerIndex("main"))) continue;

		// Set uniforms
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(object->getModelMatrix()));

		glm::vec3 colour = object->getColour();
		glUniform3f(colourLoc, colour.r, colour.g, colour.b);

		glm::vec3 scale = object->getScale();
		glUniform3f(scaleLoc, scale.x, scale.y, scale.z);

		int grid = object->getGrid();
		glUniform1i(gridLoc, grid);

		// Draw object
		glDrawElements(GL_TRIANGLES, sizeof(mainIndices) / sizeof(unsigned int), GL_UNSIGNED_INT, 0);
	}

	transformBuffer->bind();
	transformShader->bind();

	viewLoc = glGetUniformLocation(transformShader->getID(), "view");
	modelLoc = glGetUniformLocation(transformShader->getID(), "model");
	projectionLoc = glGetUniformLocation(transformShader->getID(), "projection");
	colourLoc = glGetUniformLocation(transformShader->getID(), "colour");

	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

	drawLines();

	if (selected.size() > 0 && world->getTool() != TransformTools::Tool::Select) {
		float radius = glm::length(transform[0]->getPosition() - world->getSelected()[0]->getPosition());
		glClear(GL_DEPTH_BUFFER_BIT);

		for (int i = 0; i < transform.size(); i++) {
			glm::vec4 colour = glm::vec4(transform[i]->getColour(), 1.0f);
			glUniform4f(colourLoc, colour.r, colour.g, colour.b, colour.a);
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(transform[i]->getModelMatrix()));

			// Draw object
			int size = 0;
			int offset = 0;

			switch (world->getTool()) {
			case TransformTools::Tool::Move:
				size = info.moveCount;
				offset = info.moveStart;
				break;
			case TransformTools::Tool::Scale:
				size = info.scaleCount;
				offset = info.scaleStart;
				break;
			case TransformTools::Tool::Rotate:
				size = info.scaleCount;
				offset = info.scaleStart;
				break;
			}

			glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_INT, (void*)(offset * sizeof(GLuint)));

			if (world->getTool() == TransformTools::Tool::Rotate && i % 2 == 0) {
				glm::mat4 unitMat(1.0f);
				glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(unitMat));

				glm::vec3 normal = transform[i]->getFront();
				glm::vec4 colour;
				switch (i) {
				case 0:
					colour = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
					break;
				case 2:
					colour = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
					break;
				case 4:
					colour = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
					break;
				}

				Debug::drawCircle(world->getSelected()[0]->getPosition(), normal, radius, 64, colour, colourLoc);
			}
		}
	}

	// Unbind everything
	transformBuffer->unbind();
	transformShader->unbind();
	framebuffer->unbind();
}

void Renderer::drawSkybox() {
	glDepthMask(GL_FALSE);
	glEnable(GL_DEPTH_TEST);

	skyboxShader->bind();
	skyboxBuffer->bind();

	GLuint viewLoc = glGetUniformLocation(skyboxShader->getID(), "view");
	GLuint projectionLoc = glGetUniformLocation(skyboxShader->getID(), "projection");

	glm::mat4 view = world->getCamera()->getViewMatrix();
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

	glm::mat4 projection = world->getCamera()->getProjectionMatrix(glm::vec2(texSize.x, texSize.y));
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

	glBindTexture(GL_TEXTURE_CUBE_MAP, skybox->getID());
	glDrawElements(GL_TRIANGLES, sizeof(mainIndices) / sizeof(unsigned int), GL_UNSIGNED_INT, 0);

	glDepthMask(GL_TRUE);
}

GLuint Renderer::getFramebufferTexture() {
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

void Renderer::addSkybox(std::vector<std::string> faces, std::string& skyboxShaderPath) {
	skybox = std::make_unique<Skybox>(faces);

	skyboxBuffer = std::make_unique<Buffer>(mainVertices, sizeof(mainVertices), mainIndices, sizeof(mainIndices));
	skyboxBuffer->addLayout(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);

	skyboxShader = std::make_unique<Shader>(skyboxShaderPath);
}

void Renderer::drawLines() {
	GLuint modelLoc = glGetUniformLocation(transformShader->getID(), "model");
	GLuint colourLoc = glGetUniformLocation(transformShader->getID(), "colour");

	glm::mat4 unitMat(1.0f);
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(unitMat));

	Debug::drawHitboxes(colourLoc);
}

GLuint Renderer::getTexture(const char* name) {
	for (std::shared_ptr<Texture> tex : textures) {
		if (tex->getName() == std::string(name)) {
			return tex->getID();
		}
	}

	std::cerr << "No texture with the name " << name << " was found" << std::endl;
	return 0;
}

void Renderer::setupOpenGLState() {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glEnable(GL_TEXTURE_2D);
	stbi_set_flip_vertically_on_load(true);

	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageCallback(messageCallback, 0);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, GL_FALSE);
}