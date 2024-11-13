#include "Application.h"

#include "cmds/DebugCommand.h"
#include "InteractionController.h"

Application::Application() {
	// Create a window
	succeeded;

	window = std::make_shared<Window>(1600, 900, 400, 200, "Wyvern", true, succeeded);
	if (!succeeded) {
		std::cout << "Something went wrong with GLFW/GLEW initialization or window creation" << std::endl;
		return;
	}

	// Add UI
	auto menu = window->addUI("Menu", true, 150, 0, 0, 0);
	auto properties = window->addUI("Properties", false, 0, 300, 300, 0);
	auto hierarchy = window->addUI("Hierarchy", false, menu->getHeightPtr(), 300, properties->getHeightPtr(), 0);
	auto viewport = window->addUI("Viewport", false, menu->getHeightPtr(), hierarchy->getWidthPtr(), 0, 0);

	std::shared_ptr<InteractionController> controller = std::make_shared<InteractionController>();

	menu->newZone();
	menu->addWidget(WidgetType::LargeButton, "Test1", u8"\uf0c7", std::make_shared<DebugCommand>(controller));

	// Add fonts
	FontManager::addFont("assets/SourceSansPro", 16.0f);
	FontManager::addFont("assets/FontAwesome", 16.0f, true);
	window->addFont("FontAwesome", FontType::regular);
	window->addFont("SourceSansPro", FontType::bold);
	window->addFont("SourceSansPro", FontType::regular);
}

Application::~Application() {
	
}

void Application::run() {
	if (!succeeded) return;

	// Main loop
	while (!window->shouldWindowClose()) {
		glClear(GL_COLOR_BUFFER_BIT);
		glfwPollEvents();
		window->draw();
		glfwSwapBuffers(window->get());
	}

	// End of program
	window->terminate();
}