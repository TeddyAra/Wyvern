#pragma once

#define GLEW_STATIC
#include "GL/glew.h"
#include "GLFW/glfw3.h"

class Framebuffer {
public:
	Framebuffer(int width, int height);
	~Framebuffer();

	GLuint getID();
	GLuint getTexture();

	void bind();
	void unbind();

	void updateTextureSize(int width, int height);

private:
	GLuint ID;
	GLuint texture, RBO;
};