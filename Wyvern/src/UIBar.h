#pragma once 

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <string>
#include <memory>

class UIBar {
public:
	UIBar(GLFWwindow* window, std::string name, int width, int height, int posX, int posY);
	~UIBar();

	void draw();

private:
	GLFWwindow* window;
	std::string name;
	glm::vec2 size;
	glm::vec2 pos;
};