#include "UIBar.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include <iostream>

UIBar::UIBar(GLFWwindow* window, std::string name, int titleBarHeight, SizeOrOffset top, SizeOrOffset right, SizeOrOffset bottom, SizeOrOffset left, bool ignoreUI)
	: window(window), name(name), ignoreUI(ignoreUI), titleBarHeight(titleBarHeight), 
	top(top), right(right), bottom(bottom), left(left), 
	width(0), height(0), fontCount(0), iconFont(nullptr), textFont(nullptr), headerFont(nullptr), widgetIndex(0)
{

}

UIBar::~UIBar() {

}

void UIBar::render() {
	calcSizeAndPos();

	ImGui::SetNextWindowPos(ImVec2(posX, posY), ImGuiCond_Always);
	ImGui::SetNextWindowSize(ImVec2(width, height), ImGuiCond_Always);

	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);

	ImGui::Begin(name.c_str(), nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);

	if (zones.size() == 0 && !ignoreUI) {
		ImGui::End();
		ImGui::PopStyleVar();
		return;
	}

	draw();

	ImGui::End();
	ImGui::PopStyleVar();
}

std::shared_ptr<int> UIBar::getWidthPtr() {
	if (width == 0) calcSizeAndPos();
	return std::shared_ptr<int>(&width);
}

std::shared_ptr<int> UIBar::getHeightPtr() {
	if (height == 0) calcSizeAndPos();
	return std::shared_ptr<int>(&height);
}

void UIBar::newZone(std::string title) {
	zones.push_back(std::make_shared<UIZone>(title));
}

void UIBar::addWidget(WidgetType type, std::string title, const char* icon, std::shared_ptr<ICommand> command) {
	if (zones.size() != 0) {
		zones[zones.size() - 1]->addWidget(type, title, icon, command);
	} else {
		std::cout << "No zone created yet!" << std::endl;
	}
}

void UIBar::addFont(std::string font, FontType fontType) {
	switch (fontCount) {

	case 0:
		iconFont = FontManager::getFont(font, fontType);
		break;

	case 1:
		headerFont = FontManager::getFont(font, fontType);
		break;

	case 2:
		textFont = FontManager::getFont(font, fontType);
		break;
	}

	fontCount++;
}

void UIBar::calcSizeAndPos() {
	int windowWidth, windowHeight;
	glfwGetWindowSize(window, &windowWidth, &windowHeight);
	windowHeight -= titleBarHeight;

	ImVec2 pos = ImVec2(0, titleBarHeight);
	ImVec2 imSize = ImVec2(windowWidth, windowHeight);

	if (std::holds_alternative<int>(top)) {
		int amount = std::get<int>(top);
		if (amount != 0)
			imSize.y = amount;
	} else {
		int amount = *std::get<std::shared_ptr<int>>(top);
		imSize.y -= amount;
		pos.y += amount;
	}

	if (std::holds_alternative<int>(right)) {
		int amount = std::get<int>(right);
		if (amount != 0) {
			imSize.x = amount;
			pos.x = windowWidth - amount;
		}
	} else {
		int amount = *std::get<std::shared_ptr<int>>(right);
		imSize.x -= amount;
	}

	if (std::holds_alternative<int>(bottom)) {
		int amount = std::get<int>(bottom);
		if (amount != 0) {
			imSize.y = amount;
			pos.y = windowHeight + titleBarHeight - amount;
		}
	} else {
		int amount = *std::get<std::shared_ptr<int>>(bottom);
		imSize.y -= amount;
	}

	if (std::holds_alternative<int>(left)) {
		int amount = std::get<int>(left);
		if (amount != 0)
			imSize.x = amount;
	} else {
		int amount = *std::get<std::shared_ptr<int>>(left);
		imSize.x -= amount;
		pos.x += amount;
	}

	width = imSize.x;
	height = imSize.y;
	posX = pos.x;
	posY = pos.y;
}