#pragma once 

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <string>
#include <memory>
#include <variant>

#include "UIZone.h"
#include "FontManager.h"
#include "ICommand.h"

using SizeOrOffset = std::variant<int, std::shared_ptr<int>>;

class UIBar {
public:
	UIBar(GLFWwindow* window, std::string name, bool horizontal, int titleBarHeight, SizeOrOffset top, SizeOrOffset right, SizeOrOffset bottom, SizeOrOffset left);

	~UIBar();

	void draw();
	void horizontalDraw();
	void verticalDraw();
	std::shared_ptr<int> getWidthPtr();
	std::shared_ptr<int> getHeightPtr();
	void newZone(std::string title);
	void addWidget(WidgetType type, std::string title, const char* icon, std::shared_ptr<ICommand> command);
	void addFont(std::string font, FontType type);

private:
	GLFWwindow* window;
	std::string name;
	int width;
	int height;
	int titleBarHeight;
	bool horizontal;

	SizeOrOffset top;
	SizeOrOffset right;
	SizeOrOffset bottom;
	SizeOrOffset left;

	int fontCount;
	ImFont* headerFont;
	ImFont* textFont;
	ImFont* iconFont;

	std::vector<std::shared_ptr<UIZone>> zones;
};