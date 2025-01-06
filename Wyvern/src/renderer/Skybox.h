#pragma once

#include "Renderer.h"

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