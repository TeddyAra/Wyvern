#pragma once

#define GLEW_STATIC
#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <string>
#include <vector>
#include <memory>
#include <Windows.h>
#include <WinUser.h>

#include "UIBar.h"
#include "TitleBar.h"

class Window {
public:
	Window(int width, int height, int minimumWidth, int minimumHeight, std::string name, bool hideTitleBar, bool& succeeded);
	~Window();

	bool shouldWindowClose();
	GLFWwindow* get();
	void terminate();
	void addUI(std::string name, int width, int height, int posX, int posY);
	void draw();

private:
	GLFWwindow* window;
	std::vector<std::shared_ptr<UIBar>> ui;
	std::unique_ptr<TitleBar> titleBar;
	bool titleBarHidden;

	bool dragging;
	bool resizing;
	bool top;
	bool right;
	bool bottom;
	bool left;
	ImVec2 globalCursorPos;
	ImVec2 winStartPos;
	ImVec2 winStartSize;
	ImVec2 minWinSize;

	HCURSOR cursorDiagonalRight;
	HCURSOR cursorDiagonalLeft;
	HCURSOR cursorHorizontal;
	HCURSOR cursorVertical;
	HCURSOR cursorNormal;

	void checkResize();
	void checkMove();
};