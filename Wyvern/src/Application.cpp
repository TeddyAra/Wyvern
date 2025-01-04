#include "Application.h"

#include <windows.h>
#include <iostream>
#include <string>

#include "DebugCommand.h"
#include "UndoCommand.h"
#include "RedoCommand.h"
#include "CreateObjectCommand.h"
#include "SwitchToolCommand.h"
#include "TransformTools.h"

#include "InteractionController.h"
#include "World.h"
#include "Renderer.h"

std::string getExecutablePath() {
	char buffer[MAX_PATH];
	GetModuleFileNameA(NULL, buffer, MAX_PATH);
	std::string exePath = std::string(buffer);
	size_t pos = exePath.find_last_of("\\/");
	return exePath.substr(0, pos);
}

Application::Application() {
	std::string exeDirectory = getExecutablePath();
	std::string assetsPath = exeDirectory + "/assets/";

	// Create a window
	succeeded;

	window = std::make_shared<Window>(1600, 900, 1020, 670, "Wyvern", false, succeeded);
	if (!succeeded) {
		std::cout << "Something went wrong with GLFW/GLEW initialization or window creation" << std::endl;
		return;
	}

	// Add physics layers
	Physics::addLayer(0, "main");
	Physics::addLayer(1, "transform");
	Physics::addLayer(2, "move");
	Physics::addLayer(3, "scale");
	Physics::addLayer(4, "rotate");

	// Create world and interaction controller
	world = std::make_shared<World>(Physics::getLayerIndex("main"));
	std::shared_ptr<InteractionController> controller = std::make_shared<InteractionController>(world);

	// Path to shaders
	std::string mainShaderPath = assetsPath + "mainShader.shader";
	std::string transformShaderPath = assetsPath + "transformShader.shader";
	std::string skyboxShaderPath = assetsPath + "skyboxShader.shader";

	// Add UI
	auto menu = window->addUI(UIType::Menu, "Menu", 150, 0, 0, 0);
	auto properties = window->addUI(UIType::List, "Properties", 0, 300, 300, 0);
	auto hierarchy = window->addUI(UIType::List, "Hierarchy", menu->getHeightPtr(), 300, properties->getHeightPtr(), 0);
	auto viewport = window->addViewport("Viewport", menu->getHeightPtr(), hierarchy->getWidthPtr(), 0, 0, world, mainShaderPath, transformShaderPath);

	menu->newZone("Clipboard");
	menu->addWidget(WidgetType::LargeButton, "Paste",		u8"\uf0ea", nullptr);
	menu->addWidget(WidgetType::SmallButton, "Copy",		u8"\uf0c5", nullptr);
	menu->addWidget(WidgetType::SmallButton, "Cut",			u8"\uf0c4", nullptr);
	menu->addWidget(WidgetType::SmallButton, "Duplicate",	u8"\uf0fe", nullptr);

	menu->newZone("Tools");
	menu->addWidget(WidgetType::LargeButton, "Select",	u8"\uf245", std::make_shared<SwitchToolCommand>(controller, TransformTools::Tool::Select));
	menu->addWidget(WidgetType::LargeButton, "Move",	u8"\uf0b2", std::make_shared<SwitchToolCommand>(controller, TransformTools::Tool::Move));
	menu->addWidget(WidgetType::LargeButton, "Scale",	u8"\uf065", std::make_shared<SwitchToolCommand>(controller, TransformTools::Tool::Scale));
	menu->addWidget(WidgetType::LargeButton, "Rotate",	u8"\uf021", std::make_shared<SwitchToolCommand>(controller, TransformTools::Tool::Rotate));

	menu->newZone("Snapping");
	menu->addWidget(WidgetType::Toggle, "Rotate", "", nullptr);
	menu->addWidget(WidgetType::Toggle, "Move", "", nullptr);
	menu->addWidget(WidgetType::Empty, "", "", nullptr);
	menu->addWidget(WidgetType::InputFloat, "", "", nullptr);
	menu->addWidget(WidgetType::InputFloat, "", "", nullptr);

	menu->newZone("Parts");
	menu->addWidget(WidgetType::LargeButton, "Create", u8"\uf1b2", std::make_shared<CreateObjectCommand>(controller));
	menu->addWidget(WidgetType::LargeButton, "Colour", u8"\uf1fc", nullptr);

	menu->newZone("Test");
	menu->addWidget(WidgetType::SmallButton, "Play", u8"\uf04b", nullptr);
	menu->addWidget(WidgetType::SmallButton, "Stop", u8"\uf04d", nullptr);

	// Add textures
	std::shared_ptr<Renderer> renderer = viewport->getRenderer();
	renderer->addTexture("polyfoam", std::string(assetsPath + "polyfoam.png").c_str());

	// Add a skybox to the world
	std::vector<std::string> faces = {
		assetsPath + "right.png",
		assetsPath + "left.png",
		assetsPath + "down.png",
		assetsPath + "up.png",
		assetsPath + "front.png",
		assetsPath + "back.png"
	};

	viewport->getRenderer()->addSkybox(faces, skyboxShaderPath);

	// Add fonts
	FontManager::addFont(assetsPath + "SourceSansPro", 16.0f);
	FontManager::addFont(assetsPath + "FontAwesome", 16.0f, true);
	window->addFont("FontAwesome", FontType::regular);
	window->addFont("SourceSansPro", FontType::bold);
	window->addFont("SourceSansPro", FontType::regular);
}

Application::~Application() {
	
}

void Application::run() {
	if (!succeeded) return;

	world->start();

	// Main loop
	while (!window->shouldWindowClose()) {
		glfwPollEvents();
		world->update();
		window->draw();
		glfwSwapBuffers(window->get());
	}

	// End of program
	window->terminate();
}