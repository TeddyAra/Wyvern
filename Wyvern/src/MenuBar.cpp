#include "MenuBar.h"

#include <iostream>

#include "FontManager.h"

// TODO:	Add minimum window size
//			Fix cursors for corners
//			Fix bouncy UI
//			Make it so you can't resize when moving

MenuBar::MenuBar(GLFWwindow* window, int height)
	: window(window), height(height), dragging(false), currentCursor(0)
{

}

MenuBar::~MenuBar() {

}

void MenuBar::draw() {
	// Get window size
	int windowWidth, windowHeight;
	glfwGetWindowSize(window, &windowWidth, &windowHeight);

	// Set bar position and size
	ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
	ImGui::SetNextWindowSize(ImVec2(windowWidth, height), ImGuiCond_Always);

	// Remove rounding, minimum size, and padding
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(25, 25));
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));

	// Bar
	ImGui::Begin("MenuBar", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar);

	// Check if the user is moving or resizing the window
	if (!checkResize())
		checkMove();

	// Get the font
	ImFont* font = FontManager::getFont(0, FontType::bold);
	if (font != nullptr)
		ImGui::PushFont(font);

	// Bar elements
	ImGui::Button("FILE", ImVec2(50, 25));
	ImGui::Text("Hi");

	// End of bar
	ImGui::PopFont();
	ImGui::End();
	ImGui::PopStyleVar(3);
}

void MenuBar::checkMove() {
	// Check if bar is being hovered over
	bool hovering = ImGui::IsWindowHovered() && !ImGui::IsAnyItemHovered();

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

bool MenuBar::checkResize() {
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
			ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeNESW);
		} else if ((top && left) || (bottom && right)) {
			ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeNWSE);
		} else if (left || right) {
			ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeEW);
		} else if (top || bottom) {
			ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeNS);
		} else {
			ImGui::SetMouseCursor(ImGuiMouseCursor_Arrow);
		}

		if (ImGui::IsMouseDown(0) && top + right + bottom + left != 0) {
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
			return true;
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
			glfwSetWindowSize(window, winWidth, winStartSize.y - delta.y);
			glfwSetWindowPos(window, winX, winStartPos.y + delta.y);
		}

		if (right) {
			glfwGetWindowSize(window, &winWidth, &winHeight);
			glfwSetWindowSize(window, winStartSize.x + delta.x, winHeight);
		}

		if (bottom) {
			glfwGetWindowSize(window, &winWidth, &winHeight);
			glfwSetWindowSize(window, winWidth, winStartSize.y + delta.y);
		}

		if (left) {
			glfwGetWindowSize(window, &winWidth, &winHeight);
			glfwGetWindowPos(window, &winX, &winY);
			glfwSetWindowSize(window, winStartSize.x - delta.x, winHeight);
			glfwSetWindowPos(window, winStartPos.x + delta.x, winY);
		}

		if (!ImGui::IsMouseDown(0)) {
			resizing = false;
		}

		return true;
	}

	return false;
}