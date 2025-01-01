#pragma once

#define GLEW_STATIC
#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <vector>
#include <string>

#include "stb_image/stb_image.h"

class Skybox {
public:
	Skybox(std::vector<std::string> faces);
	~Skybox();

	GLuint getID();

private:
	GLuint ID;
};