#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "FontManager.h"

#include <memory>
#include <string>

class TitleBar {
public:
	TitleBar(GLFWwindow* window, int height);
	~TitleBar();

	void draw();
	bool isHovering();
	void addFont(std::string font, FontType type);

private:
	void checkHover();

	GLFWwindow* window; 
	int fontCount;
	ImFont* headerFont;
	ImFont* textFont;
	ImFont* iconFont;
	int height;
	bool hovering;
};