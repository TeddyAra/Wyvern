#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <stdexcept>
#include <iostream>
#include <memory>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "Window.h"
#include "FontManager.h"

class Application {
public:
	Application();
	~Application();

	void run();

private:
	std::shared_ptr<Window> window;
	std::shared_ptr<World> world;
	bool succeeded;
};