#pragma once

#include "Renderer.h"

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