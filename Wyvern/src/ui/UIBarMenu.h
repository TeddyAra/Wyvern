#pragma once
#pragma warning( disable : 4244 ) 
#pragma warning( disable : 4018 ) 

#include "UIBar.h"

class UIBarMenu : public UIBar {
public:
	UIBarMenu(GLFWwindow* window, std::string name, int titleBarHeight, SizeOrOffset top, SizeOrOffset right, SizeOrOffset bottom, SizeOrOffset left, bool ignoreUI)
		: UIBar(window, name, titleBarHeight, top, right, bottom, left, ignoreUI) {}
	void draw() override;
	void drawBigButton(std::vector<std::shared_ptr<UIWidget>> widgets, int index) override;
	void drawSmallButton(std::vector<std::shared_ptr<UIWidget>> widgets, int index) override;
	void drawToggle(std::vector<std::shared_ptr<UIWidget>> widgets, int index) override;
	void drawInputFloat(std::vector<std::shared_ptr<UIWidget>> widgets, int index) override;
	void drawText(std::vector<std::shared_ptr<UIWidget>> widgets, int index, bool shortText) override;

private:
	int padding = 15;
	int topOffset = 20;
	int textHeight = 10;
	int bigHeight = 150 - 2 * padding - topOffset - 6;
	int smallHeight = (bigHeight - 2 * padding) / 3 - 2;
	int posX = padding;
	int originalY = topOffset + padding;
	int posY = originalY;
	int smallWidth = 60;
	int bigWidth = 90;
	int smallWidgetCount = 0;
	int minX = posX;
	bool shortText;

	void updatePos();
};