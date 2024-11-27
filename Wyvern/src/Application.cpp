#include "Application.h"

#include "DebugCommand.h"
#include "UndoCommand.h"
#include "RedoCommand.h"
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
	auto menu = window->addUI(UIType::Menu, "Menu", 150, 0, 0, 0);
	auto properties = window->addUI(UIType::List, "Properties", 0, 300, 300, 0);
	auto hierarchy = window->addUI(UIType::List, "Hierarchy", menu->getHeightPtr(), 300, properties->getHeightPtr(), 0);
	auto viewport = window->addUI(UIType::View, "Viewport", menu->getHeightPtr(), hierarchy->getWidthPtr(), 0, 0, true);

	std::shared_ptr<InteractionController> controller = std::make_shared<InteractionController>();

	menu->newZone("Zone 1");
	menu->addWidget(WidgetType::InputFloat,		"Debug", u8"\uf0c7",	std::make_shared<DebugCommand>(controller));
	menu->addWidget(WidgetType::SmallButton,	"Undo", u8"\uf0c7",		std::make_shared<UndoCommand>(controller));
	menu->addWidget(WidgetType::SmallButton,	"Redo", u8"\uf0c7",		std::make_shared<RedoCommand>(controller));

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