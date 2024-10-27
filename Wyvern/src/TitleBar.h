#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"

#include <memory>

class TitleBar {
public:
	TitleBar(GLFWwindow* window, int height);
	~TitleBar();

	void draw();
	bool isHovering();

private:
	void checkHover();

	GLFWwindow* window;
	int height;
	bool hovering;
};