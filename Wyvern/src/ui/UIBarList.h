#pragma once
#pragma warning( disable : 4244 ) 

#include "UIBar.h"

class UIBarList : public UIBar {
public:
	UIBarList(GLFWwindow* window, std::string name, int titleBarHeight, SizeOrOffset top, SizeOrOffset right, SizeOrOffset bottom, SizeOrOffset left)
		: UIBar(window, name, titleBarHeight, top, right, bottom, left) {}
	void draw() override;
	void drawBigButton(std::vector<std::shared_ptr<UIWidget>> widgets, int index) override;
	void drawSmallButton(std::vector<std::shared_ptr<UIWidget>> widgets, int index) override;
	void drawToggle(std::vector<std::shared_ptr<UIWidget>> widgets, int index) override;
	void drawInputFloat(std::vector<std::shared_ptr<UIWidget>> widgets, int index) override;

private:
	int topOffset = 24;
	int padding = 15;
	int posY = 0;
	int leftPosX = padding;
	int leftSize = 70;
	int rightSize;
	int height = 30;
	int rightPosXMin = leftPosX + leftSize + padding;
	int rightPosXMax;
};