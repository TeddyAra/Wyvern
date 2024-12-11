#pragma once

#define GLEW_STATIC
#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "stb_image/stb_image.h"

class Texture {
public:
	Texture(const char* texturePath, GLenum textureUnit = GL_TEXTURE0);
	~Texture();

	GLuint getID();

private:
	GLuint ID;
};