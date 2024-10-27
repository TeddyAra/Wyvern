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

	// Add font and UI
	FontManager::addFont("assets/SourceSansPro", 16.0f);
	window->addUI("Two", 1600, 100, 0, 25);

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