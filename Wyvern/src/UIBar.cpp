#include "UIBar.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"

#include <iostream>

UIBar::UIBar(GLFWwindow* window, std::string name, bool horizontal, int titleBarHeight, SizeOrOffset top, SizeOrOffset right, SizeOrOffset bottom, SizeOrOffset left)
	: window(window), name(name), horizontal(horizontal), titleBarHeight(titleBarHeight), 
	top(top), right(right), bottom(bottom), left(left), 
	width(0), height(0), fontCount(0), iconFont(nullptr), textFont(nullptr), headerFont(nullptr)
{

}

UIBar::~UIBar() {

}

void UIBar::draw() {
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

	ImGui::SetNextWindowPos(pos, ImGuiCond_Always);
	ImGui::SetNextWindowSize(imSize, ImGuiCond_Always);

	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);

	ImGui::Begin(name.c_str(), nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);

	if (zones.size() == 0) {
		ImGui::End();
		ImGui::PopStyleVar();
		return;
	}

	ImGui::Columns(zones.size());

	for (int i = 0; i < zones.size(); i++) {
		std::vector<UIWidget> widgets = zones[i].getWidgets();

		int smallWidgetCount = -1;
		ImGui::BeginGroup();

		for (int j = 0; j < widgets.size(); j++) {
			smallWidgetCount++;
			ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 1);

			switch (widgets[j].getType()) {
			case WidgetType::LargeButton:
				ImGui::PushFont(iconFont);
				ImGui::SetWindowFontScale(1.5f);
				ImGui::Button(widgets[j].getIcon(), ImVec2(60, 70));
				ImGui::SetWindowFontScale(1.0f);
				ImGui::PopFont();

				ImGui::PushFont(headerFont);
				ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 30 - (ImGui::CalcTextSize(widgets[j].getTitle().c_str()).x / 2));
				ImGui::Text(widgets[j].getTitle().c_str(), ImVec2(60, 10));
				ImGui::PopFont();

				smallWidgetCount--;
				ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 1);
				break;

			case WidgetType::SmallButton:
				ImGui::PushFont(headerFont);
				ImGui::Button(std::string(widgets[j].getTitle()).c_str(), ImVec2(90, 20));
				ImGui::PopFont();
				break;
			}

			if (smallWidgetCount == -1) {
				ImGui::EndGroup();
				ImGui::SameLine();
				ImGui::BeginGroup();
			}
		}

		ImGui::EndGroup();

		if (i != zones.size() - 1) 
			ImGui::NextColumn();
	}

	ImGui::End();

	ImGui::PopStyleVar();
}

std::shared_ptr<int> UIBar::getWidthPtr() {
	return std::shared_ptr<int>(&width);
}

std::shared_ptr<int> UIBar::getHeightPtr() {
	return std::shared_ptr<int>(&height);
}

void UIBar::newZone() {
	zones.push_back(UIZone());
}

void UIBar::addWidget(WidgetType type, std::string title, const char* icon, std::function<void()> function) {
	if (zones.size() != 0) {
		zones[zones.size() - 1].addWidget(type, title, icon, function);
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