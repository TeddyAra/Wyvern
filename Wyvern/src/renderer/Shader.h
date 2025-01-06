#pragma once

#include "Renderer.h"

#include <string>

class Shader {
public:
	Shader(std::string& shaderPath);
	~Shader();

	GLuint getID();
	void bind();
	void unbind();

private:
	GLuint ID;

	void readFile(std::string& shaderPath, std::string& vertexSource, std::string& fragmentSource);
	GLuint compileShader(GLenum type, const char* source);
	void linkProgram(GLuint vertexShader, GLuint fragmentShader);
};