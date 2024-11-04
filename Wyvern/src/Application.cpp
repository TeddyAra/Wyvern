#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <stdexcept>
#include <iostream>
#include <memory>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"

#include "Window.h"
#include "FontManager.h"

int main() {
	// Create a window
	bool succeeded;

	std::shared_ptr<Window> window = std::make_shared<Window>(1600, 900, 400, 200, "Wyvern", true, succeeded);
	if (!succeeded) {
		std::cout << "Something went wrong with GLFW/GLEW initialization or window creation" << std::endl;
		return -1;
	}

	// Add UI
	auto menu = window->addUI("Menu", true, 150, 0, 0, 0);
	auto properties = window->addUI("Properties", false, 0, 300, 300, 0);
	auto hierarchy = window->addUI("Hierarchy", false, menu->getHeightPtr(), 300, properties->getHeightPtr(), 0);
	auto viewport = window->addUI("Viewport", false, menu->getHeightPtr(), hierarchy->getWidthPtr(), 0, 0);

	menu->newZone();
	menu->addWidget(WidgetType::LargeButton, "Test1", u8"\uf0c7", NULL);
	menu->addWidget(WidgetType::SmallButton, "Test2", NULL, NULL);
	menu->addWidget(WidgetType::SmallButton, "Test3", NULL, NULL);
	menu->addWidget(WidgetType::SmallButton, "Test4", NULL, NULL);

	// Add fonts
	FontManager::addFont("assets/SourceSansPro", 16.0f);
	FontManager::addFont("assets/FontAwesome", 16.0f, true);
	window->addFont("FontAwesome", FontType::regular);
	window->addFont("SourceSansPro", FontType::bold);
	window->addFont("SourceSansPro", FontType::regular);

	// Main loop
	while (!window->shouldWindowClose()) {
		glClear(GL_COLOR_BUFFER_BIT);
		glfwPollEvents();
		window->draw();
		glfwSwapBuffers(window->get());
	}

	// End of program
	window->terminate();
	return 0;
}