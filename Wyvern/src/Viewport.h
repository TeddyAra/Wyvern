#pragma once

#include <memory>
#include <iostream>
#include <string>

#include "UIBar.h"
#include "Renderer.h"

class Viewport : public UIBar {
public:
	Viewport(GLFWwindow* window, std::string name, int titleBarHeight, SizeOrOffset top, SizeOrOffset right, SizeOrOffset bottom, SizeOrOffset left, bool ignoreUI, std::shared_ptr<World> world, std::string& mainShaderPath, std::string& transformShaderPath)
		: UIBar(window, name, titleBarHeight, top, right, bottom, left, ignoreUI), renderer(std::make_shared<Renderer>(window, world, mainShaderPath, transformShaderPath)), resized(false) 
	{
		//glfwSetWindowUserPointer(window, this);
		if (viewportInstance) {
			delete this;
		}

		viewportInstance = this;
		glfwSetFramebufferSizeCallback(window, sizeCallback);
	}
	void draw() override;
	void drawBigButton(std::vector<std::shared_ptr<UIWidget>> widgets, int index) override {};
	void drawSmallButton(std::vector<std::shared_ptr<UIWidget>> widgets, int index) override {};
	void drawToggle(std::vector<std::shared_ptr<UIWidget>> widgets, int index) override {};
	void drawInputFloat(std::vector<std::shared_ptr<UIWidget>> widgets, int index) override {};

	void clear();
	void resize();
	static void sizeCallback(GLFWwindow* window, int width, int height);
	std::shared_ptr<Renderer> getRenderer();

private:
	std::shared_ptr<Renderer> renderer;
	bool resized;
	static Viewport* viewportInstance;
	static Viewport* getViewport();
};