#include "TitleBar.h"

#include <iostream>

#include "FontManager.h"

TitleBar::TitleBar(GLFWwindow* window, int height)
	: window(window), height(height), hovering(false)
{

}

TitleBar::~TitleBar() {

}

void TitleBar::draw() {
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

	// Check if the user is hovering over the title bar
	checkHover();

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

bool TitleBar::isHovering() {
	return hovering;
}

void TitleBar::checkHover() {
	// Check if bar is being hovered over
	hovering = ImGui::IsWindowHovered() && !ImGui::IsAnyItemHovered();
}