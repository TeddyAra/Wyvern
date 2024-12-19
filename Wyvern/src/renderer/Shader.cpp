#include "Shader.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

Shader::Shader(std::string& shaderPath) {
	std::string vertexSource;
	std::string fragmentSource;
	readFile(shaderPath, vertexSource, fragmentSource);

	GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexSource.c_str());
	GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentSource.c_str());
	linkProgram(vertexShader, fragmentShader);
}

Shader::~Shader() {

}

GLuint Shader::getID() {
	return ID;
}

void Shader::bind() {
	glUseProgram(ID);
}

void Shader::unbind() {
	glUseProgram(0);
}

void Shader::readFile(std::string& shaderPath, std::string& vertexSource, std::string& fragmentSource) {
	std::ifstream stream(shaderPath);

	enum class ShaderType {
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	std::string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;
	while (getline(stream, line)) {
		if (line.find("#shader") != std::string::npos) {
			if (line.find("vertex") != std::string::npos) {
				type = ShaderType::VERTEX;
			} else if (line.find("fragment") != std::string::npos) {
				type = ShaderType::FRAGMENT;
			}
		} else if (type != ShaderType::NONE) {
			ss[(int)type] << line << '\n';
		} else { 
			std::cerr << "Shader file not written correctly (must start with #shader vertex or #shader fragment)" << std::endl;
		}
	}

	vertexSource = ss[0].str();
	fragmentSource = ss[1].str();
}

GLuint Shader::compileShader(GLenum type, const char* source) {
	GLuint shader = glCreateShader(type);
	glShaderSource(shader, 1, &source, nullptr);
	glCompileShader(shader);

	GLint success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		char infoLog[512];
		glGetShaderInfoLog(shader, 512, nullptr, infoLog);
		std::cerr << "Shader compilation failed\n" << infoLog << std::endl;
	}
	return shader;
}

void Shader::linkProgram(GLuint vertexShader, GLuint fragmentShader) {
	ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);

	GLint success;
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success) {
		char infoLog[512];
		glGetProgramInfoLog(ID, 512, nullptr, infoLog);
		std::cerr << "Program linking failed\n" << infoLog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}