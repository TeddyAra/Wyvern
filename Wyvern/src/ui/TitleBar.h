#pragma once

#include "Renderer.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "FontManager.h"
#include "UIWidget.h"

#include <memory>
#include <vector>
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

	int padding = 1;
	int smallWidth = 25 - 2 * padding;
	int bigWidth = 50 - 2 * padding;
	int widgetHeight = 25 - 2 * padding;

	std::vector<std::shared_ptr<UIWidget>> widgets;
};