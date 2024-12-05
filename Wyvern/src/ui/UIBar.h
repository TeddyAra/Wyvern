#pragma once 
#pragma warning( disable : 4244 ) 

#include <string>
#include <memory>
#include <variant>

#include "UIZone.h"
#include "FontManager.h"
#include "ICommand.h"
#include "Renderer.h"

using SizeOrOffset = std::variant<int, std::shared_ptr<int>>;

class UIBar {
public:
	UIBar(GLFWwindow* window, std::string name, int titleBarHeight, SizeOrOffset top, SizeOrOffset right, SizeOrOffset bottom, SizeOrOffset left, bool ignoreUI = false);
	~UIBar();

	virtual void draw() = 0;
	virtual void drawBigButton(std::vector<std::shared_ptr<UIWidget>> widgets, int index) = 0;
	virtual void drawSmallButton(std::vector<std::shared_ptr<UIWidget>> widgets, int index) = 0;
	virtual void drawToggle(std::vector<std::shared_ptr<UIWidget>> widgets, int index) = 0;
	virtual void drawInputFloat(std::vector<std::shared_ptr<UIWidget>> widgets, int index) = 0;
	void render();
	std::shared_ptr<int> getWidthPtr();
	std::shared_ptr<int> getHeightPtr();
	void newZone(std::string title);
	void addWidget(WidgetType type, std::string title, const char* icon, std::shared_ptr<ICommand> command);
	void addFont(std::string font, FontType type);

protected:
	GLFWwindow* window;
	std::string name;
	int width;
	int height;
	int posX;
	int posY;

	bool ignoreUI;
	int titleBarHeight;
	int widgetIndex;

	SizeOrOffset top;
	SizeOrOffset right;
	SizeOrOffset bottom;
	SizeOrOffset left;

	int fontCount;
	ImFont* headerFont;
	ImFont* textFont;
	ImFont* iconFont;

	std::vector<std::shared_ptr<UIZone>> zones;

	void calcSizeAndPos();
};