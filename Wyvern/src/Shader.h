#pragma once

#define GLEW_STATIC
#include "GL/glew.h"
#include "GLFW/glfw3.h"

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