#include "MenuBar.h"

#include <iostream>

#include "FontManager.h"

MenuBar::MenuBar(GLFWwindow* window, int height)
	: window(window), height(height), dragging(false)
{

}

MenuBar::~MenuBar() {

}

void MenuBar::draw() {
	int windowWidth, windowHeight;
	glfwGetWindowSize(window, &windowWidth, &windowHeight);

	ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
	ImGui::SetNextWindowSize(ImVec2(windowWidth, height), ImGuiCond_Always);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(25, 25));
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));

	ImGui::Begin("MenuBar", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar);

	if (!dragging && ImGui::IsWindowHovered() && ImGui::IsMouseDown(0) && !ImGui::IsAnyItemHovered()) {
		dragging = true;

		int winX, winY;
		glfwGetWindowPos(window, &winX, &winY);
		winStartPos = ImVec2(winX, winY);

		double cursorX, cursorY;
		glfwGetCursorPos(window, &cursorX, &cursorY);
		globalCursorPos = ImVec2(winX + cursorX, winY + cursorY);
	} 
	
	if (dragging && !ImGui::IsMouseDown(0)) {
		dragging = false;
	}

	if (dragging) {
		int winX, winY;
		glfwGetWindowPos(window, &winX, &winY);

		double cursorX, cursorY;
		glfwGetCursorPos(window, &cursorX, &cursorY);
		ImVec2 cursorCurrentPos = ImVec2(winX + cursorX, winY + cursorY);

		ImVec2 delta = ImVec2(cursorCurrentPos.x - globalCursorPos.x, cursorCurrentPos.y - globalCursorPos.y);

		glfwSetWindowPos(window, winStartPos.x + delta.x, winStartPos.y + delta.y);
	}

	ImFont* font = FontManager::getFont(0, FontType::bold);
	if (font != nullptr)
		ImGui::PushFont(font);

	ImGui::Button("FILE", ImVec2(40, 25));
	ImGui::Text("Hi");

	ImGui::PopFont();

	ImGui::End();

	ImGui::PopStyleVar(3);
}