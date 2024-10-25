#pragma once

#define GLEW_STATIC
#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <string>
#include <vector>
#include <memory>

#include "UIBar.h"
#include "MenuBar.h"

class Window {
public:
	Window(int width, int height, std::string name, bool& succeeded);
	~Window();

	bool shouldWindowClose();
	GLFWwindow* get();
	void terminate();
	void addUI(std::string name, int width, int height, int posX, int posY);
	void draw();

private:
	GLFWwindow* window;
	std::vector<std::shared_ptr<UIBar>> ui;
	std::unique_ptr<MenuBar> menuBar;
};