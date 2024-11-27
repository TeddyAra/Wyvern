#include "Window.h"

#include <stdexcept>
#include <iostream>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"

Window::Window(int width, int height, int minimumWidth, int minimumHeight, std::string name, bool hideTitleBar, bool& succeeded)
	: window(nullptr), minWinSize(ImVec2(minimumWidth, minimumHeight)), titleBarHidden(hideTitleBar), titleBarHeight(25),
	resizing(false), dragging(false), top(false), right(false), bottom(false), left(false), prevMouse(false),
	cursorDiagonalRight(NULL), cursorDiagonalLeft(NULL), cursorHorizontal(NULL), cursorVertical(NULL), cursorNormal(NULL)
{
	// Initialize GLFW
	if (!glfwInit()) {
		succeeded = false;
		return;
	}	

	// Create a window
	if (hideTitleBar)
		glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
	window = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);

	if (!window) {
		glfwTerminate();
		succeeded = false;
		return;
	}

	glfwMakeContextCurrent(window);

	// Initialize GLEW
	if (glewInit() != GLEW_OK) {
		succeeded = false;
		return;
	}

	std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
	succeeded = true;

	glfwSwapInterval(1);

	// Initialize ImGui
	ImGui::CreateContext();
	ImGui_ImplGlfwGL3_Init(window, true);
	ImGui::StyleColorsDark();

	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;

	// Create a menu bar
	titleBar = std::make_unique<TitleBar>(window, titleBarHeight);

	cursorDiagonalRight = LoadCursor(NULL, IDC_SIZENESW);
	cursorDiagonalLeft = LoadCursor(NULL, IDC_SIZENWSE);
	cursorHorizontal = LoadCursor(NULL, IDC_SIZEWE);
	cursorVertical = LoadCursor(NULL, IDC_SIZENS);
	cursorNormal = LoadCursor(NULL, IDC_ARROW);
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

std::shared_ptr<UIBar> Window::addUI(UIType type, std::string name, SizeOrOffset top, SizeOrOffset right, SizeOrOffset bottom, SizeOrOffset left, bool ignoreUI) {
	std::shared_ptr<UIBar> bar;

	switch (type) {
	case UIType::Menu:
		bar = std::make_shared<UIBarMenu>(window, name, titleBarHeight, top, right, bottom, left, ignoreUI);
		break;

	case UIType::List:
		bar = std::make_shared<UIBarList>(window, name, titleBarHeight, top, right, bottom, left, ignoreUI);
		break;
	
	case UIType::View:
		bar = std::make_shared<Viewport>(window, name, titleBarHeight, top, right, bottom, left, ignoreUI);
		break;
	}

	if (bar) {
		ui.push_back(bar);
	}

	return bar;
}

void Window::draw() {
	if (titleBarHidden) {
		checkResize();
		checkMove();
		prevMouse = ImGui::IsMouseDown(0);
	}

	ImGui_ImplGlfwGL3_NewFrame();

	titleBar->draw();

	for (auto bar : ui) {
		if (typeid(*bar) == typeid(Viewport)) bar->render();
	}

	for (auto bar : ui) {
		if (typeid(*bar) == typeid(Viewport)) continue;
		bar->render();
	}

	ImGui::Render();
	ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

	//glfwSwapBuffers(window);
}

void Window::addFont(std::string font, FontType type) {
	titleBar->addFont(font, type);

	for (auto bar : ui) {
		bar->addFont(font, type);
	}
}

void Window::checkMove() {
	if (resizing) return;

	// Check if bar is being hovered over
	bool hovering = titleBar->isHovering();

	// Start of dragging
	if (!dragging && hovering && ImGui::IsMouseDown(0)) {
		dragging = true;

		int winX, winY;
		glfwGetWindowPos(window, &winX, &winY);
		winStartPos = ImVec2(winX, winY);

		double cursorX, cursorY;
		glfwGetCursorPos(window, &cursorX, &cursorY);
		globalCursorPos = ImVec2(winX + cursorX, winY + cursorY);
	}

	// End of dragging
	if (dragging && !ImGui::IsMouseDown(0)) {
		dragging = false;
	}

	// Dragging
	if (dragging) {
		// Get window and cursor position
		int winX, winY;
		glfwGetWindowPos(window, &winX, &winY);

		double cursorX, cursorY;
		glfwGetCursorPos(window, &cursorX, &cursorY);
		ImVec2 cursorCurrentPos = ImVec2(winX + cursorX, winY + cursorY);

		// Calculate difference in cursor position
		ImVec2 delta = ImVec2(cursorCurrentPos.x - globalCursorPos.x, cursorCurrentPos.y - globalCursorPos.y);

		// Set window to new position
		glfwSetWindowPos(window, winStartPos.x + delta.x, winStartPos.y + delta.y);
	}
}

void Window::checkResize() {
	if (dragging) return;

	if (!resizing) {
		// Get cursor position
		double cursorX, cursorY;
		glfwGetCursorPos(window, &cursorX, &cursorY);
		ImVec2 cursorPos = ImVec2(cursorX, cursorY);

		// Get window size
		int windowWidth, windowHeight;
		glfwGetWindowSize(window, &windowWidth, &windowHeight);
		ImVec2 windowSize(windowWidth, windowHeight);

		// Detect where the cursor is
		int borderDetection = 5;
		top = glm::abs(cursorPos.y) < borderDetection;
		right = glm::abs(cursorPos.x - windowSize.x) < borderDetection;
		bottom = glm::abs(cursorPos.y - windowSize.y) < borderDetection;
		left = glm::abs(cursorPos.x) < borderDetection;

		// Show the cursor
		if ((top && right) || (bottom && left)) {
			SetCursor(cursorDiagonalRight);
		} else if ((top && left) || (bottom && right)) {
			SetCursor(cursorDiagonalLeft);
		} else if (left || right) {
			SetCursor(cursorHorizontal);
		} else if (top || bottom) {
			SetCursor(cursorVertical);
		} else {
			SetCursor(cursorNormal);
		}

		if (ImGui::IsMouseDown(0) && !prevMouse && top + right + bottom + left != 0) {
			resizing = true;

			int winWidth, winHeight;
			glfwGetWindowSize(window, &winWidth, &winHeight);
			winStartSize = ImVec2(winWidth, winHeight);

			int winX, winY;
			glfwGetWindowPos(window, &winX, &winY);
			winStartPos = ImVec2(winX, winY);

			double cursorX, cursorY;
			glfwGetCursorPos(window, &cursorX, &cursorY);
			globalCursorPos = ImVec2(winX + cursorX, winY + cursorY);
		}
	} else {
		int winX, winY;
		glfwGetWindowPos(window, &winX, &winY);
		double cursorX, cursorY;
		glfwGetCursorPos(window, &cursorX, &cursorY);
		ImVec2 delta = ImVec2(winX + cursorX - globalCursorPos.x, winY + cursorY - globalCursorPos.y);

		int winWidth, winHeight;
		if (top) {
			glfwGetWindowSize(window, &winWidth, &winHeight);
			glfwGetWindowPos(window, &winX, &winY);
			int height = winStartSize.y - delta.y;
			int posY = winStartPos.y + delta.y;
			if (height < minWinSize.y) {
				height = minWinSize.y;
				posY = winStartPos.y + winStartSize.y - minWinSize.y;
			}

			glfwSetWindowSize(window, winWidth, height);
			glfwSetWindowPos(window, winX, posY);
		}

		if (right) {
			glfwGetWindowSize(window, &winWidth, &winHeight);
			int width = winStartSize.x + delta.x;
			if (width < minWinSize.x) width = minWinSize.x;

			glfwSetWindowSize(window, width, winHeight);
		}

		if (bottom) {
			glfwGetWindowSize(window, &winWidth, &winHeight);
			int height = winStartSize.y + delta.y;
			if (height < minWinSize.y) height = minWinSize.y;

			glfwSetWindowSize(window, winWidth, height);
		}

		if (left) {
			glfwGetWindowSize(window, &winWidth, &winHeight);
			glfwGetWindowPos(window, &winX, &winY);
			int width = winStartSize.x - delta.x;
			int posX = winStartPos.x + delta.x;
			if (width < minWinSize.x) {
				width = minWinSize.x;
				posX = winStartPos.x + winStartSize.x - minWinSize.x;
			}
			glfwSetWindowSize(window, width, winHeight);
			glfwSetWindowPos(window, posX, winY);
		}

		if (!ImGui::IsMouseDown(0)) {
			resizing = false;
		}
	}
}