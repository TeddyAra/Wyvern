#pragma once

#include <GL/glew.h>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <WinUser.h>

#include <string>
#include <vector>
#include <memory>
#include <variant>

#include "UIBar.h"
#include "UIBarMenu.h"
#include "UIBarList.h"
#include "Viewport.h"
#include "Renderer.h"
#include "Input.h"

#include "TitleBar.h"
#include "FontManager.h"

using SizeOrOffset = std::variant<int, std::shared_ptr<int>>;

enum TextType {
	header,
	text
};

enum UIType {
	List,
	Menu
};

class Window {
public:
	Window(int width, int height, int minimumWidth, int minimumHeight, std::string name, bool hideTitleBar, bool& succeeded);
	~Window();

	bool shouldWindowClose();
	GLFWwindow* get();
	void terminate();
	/**
	 * @brief Adds UI that can be docked
	 *
	 * @param name: Name of the UI
	 * @param top, right, bottom, left: The size or offset the UI uses to scale and position itself. If this parameter is an integer, it'll act as the size, with the UI locked to whichever side this param is. If this parameter is a shared pointer, it'll act as an offset, where the UI will scale to move away from whichever side this param is.
	 *
	 * @return Returns the created UI bar
	 */
	std::shared_ptr<UIBar> addUI(UIType type, std::string name, SizeOrOffset top, SizeOrOffset right, SizeOrOffset bottom, SizeOrOffset left, bool ignoreUI = false);
	std::shared_ptr<Viewport> addViewport(std::string name, SizeOrOffset top, SizeOrOffset right, SizeOrOffset bottom, SizeOrOffset left, std::shared_ptr<World> world, std::string& mainShaderPath, std::string& transformShaderPath);
	void sizeCallback(GLFWwindow* window, int width, int height);
	void draw();
	void addFont(std::string font, FontType type);

private:
	GLFWwindow* window;
	std::vector<std::shared_ptr<UIBar>> ui;
	std::unique_ptr<TitleBar> titleBar;
	std::shared_ptr<Viewport> viewport;
	int titleBarHeight;
	bool titleBarHidden;

	bool dragging;
	bool resizing;
	bool top;
	bool right;
	bool bottom;
	bool left;
	bool prevMouse;

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