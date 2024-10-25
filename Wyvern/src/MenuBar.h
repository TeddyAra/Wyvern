#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"

#include <memory>

class MenuBar {
public:
	MenuBar(GLFWwindow* window, int height);
	~MenuBar();

	void draw();

private:
	GLFWwindow* window;
	int height;
	bool dragging;
	ImVec2 globalCursorPos;
	ImVec2 winStartPos;
};