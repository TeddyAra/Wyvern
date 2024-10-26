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
	void checkMove();
	bool checkResize();

	GLFWwindow* window;
	int currentCursor;
	int height;
	bool dragging;
	bool resizing;
	bool top;
	bool right;
	bool bottom;
	bool left;
	ImVec2 globalCursorPos;
	ImVec2 winStartPos;
	ImVec2 winStartSize;
};