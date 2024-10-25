#include "Window.h"

#include <stdexcept>
#include <iostream>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"

Window::Window(int width, int height, std::string name, bool& succeeded)
	: window(nullptr)
{
	if (!glfwInit()) {
		succeeded = false;
		return;
	}	

	glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
	window = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);
	if (!window) {
		glfwTerminate();
		succeeded = false;
		return;
	}

	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK) {
		succeeded = false;
		return;
	}

	std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
	succeeded = true;

	ImGui::CreateContext();
	ImGui_ImplGlfwGL3_Init(window, true);
	ImGui::StyleColorsDark();

	menuBar = std::make_unique<MenuBar>(window, 25);
}

Window::~Window() {
	//terminate();
}

bool Window::shouldWindowClose() {
	return glfwWindowShouldClose(window);
}

GLFWwindow* Window::get() {
	return window;
}

void Window::terminate() {
	glfwTerminate();
	ImGui_ImplGlfwGL3_Shutdown();
	ImGui::DestroyContext();
}

void Window::addUI(std::string name, int width, int height, int posX, int posY) {
	ui.push_back(std::make_shared<UIBar>(window, name, width, height, posX, posY));
}

void Window::draw() {
	ImGui_ImplGlfwGL3_NewFrame();

	for (auto bar : ui) {
		bar->draw();
	}

	menuBar->draw();

	ImGui::Render();
	ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
}