#pragma once

#include <memory>
#include <iostream>

#include "UIBar.h"
#include "Renderer.h"

class Viewport : public UIBar {
public:
	Viewport(GLFWwindow* window, std::string name, int titleBarHeight, SizeOrOffset top, SizeOrOffset right, SizeOrOffset bottom, SizeOrOffset left, bool ignoreUI)
		: UIBar(window, name, titleBarHeight, top, right, bottom, left, ignoreUI), renderer(std::make_unique<Renderer>(window)), resized(false) {}
	void draw() override;
	void drawBigButton(std::vector<std::shared_ptr<UIWidget>> widgets, int index) override {};
	void drawSmallButton(std::vector<std::shared_ptr<UIWidget>> widgets, int index) override {};
	void drawToggle(std::vector<std::shared_ptr<UIWidget>> widgets, int index) override {};
	void drawInputFloat(std::vector<std::shared_ptr<UIWidget>> widgets, int index) override {};

	void clear();
	void resize();

private:
	std::unique_ptr<Renderer> renderer;
	bool resized;
};