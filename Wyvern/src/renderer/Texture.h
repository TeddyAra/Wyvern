#pragma once

#include "Renderer.h"

#include <string>

#include "stb_image/stb_image.h"

class Texture {
public:
	Texture(const char* name, const char* texturePath, GLenum textureUnit = GL_TEXTURE0);
	~Texture();

	GLuint getID();
	std::string& getName();

private:
	std::string name;
	GLuint ID;
};