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

	if (horizontal) {
		horizontalDraw();
	} else {
		verticalDraw();
	}

	ImGui::End();

	ImGui::PopStyleVar();
}

void UIBar::horizontalDraw() {
	int padding = 15;
	int topOffset = 24;
	int textHeight = 10;
	int bigHeight = 150 - 2 * padding - topOffset - 6;
	int smallHeight = (bigHeight - 2 * padding) / 3 - 2;
	int posX = padding;
	int originalY = topOffset + padding;
	int posY = originalY;
	int smallWidth = 60;
	int bigWidth = 90;

	for (int i = 0; i < zones.size(); i++) {
		ImGui::PushID(i);
		std::vector<std::shared_ptr<UIWidget>> widgets = zones[i]->getWidgets();

		int smallWidgetCount = 0;
		int minX = posX;

		for (int j = 0; j < widgets.size(); j++) {
			ImGui::SetCursorPosX(posX);
			ImGui::SetCursorPosY(posY);

			switch (widgets[j]->getType()) {
			case WidgetType::LargeButton:
				if (smallWidgetCount != 0) {
					posY = originalY;
					posX += bigWidth + padding;
					smallWidgetCount = 0;

					ImGui::SetCursorPosX(posX);
					ImGui::SetCursorPosY(posY);
				}

				ImGui::PushFont(iconFont);
				ImGui::SetWindowFontScale(1.5f);
				if (ImGui::Button(widgets[j]->getIcon(), ImVec2(60, bigHeight))) {
					widgets[j]->execute();
				}
				ImGui::SetWindowFontScale(1.0f);
				ImGui::PopFont();

				ImGui::SetCursorPosX(posX + smallWidth / 2 - (ImGui::CalcTextSize(widgets[j]->getTitle().c_str()).x / 2));
				ImGui::SetCursorPosY(posY + bigHeight - 20);

				ImGui::PushFont(headerFont);
				ImGui::Text(widgets[j]->getTitle().c_str(), ImVec2(smallWidth, 10));
				ImGui::PopFont();

				posX += smallWidth + padding;
				break;

			case WidgetType::SmallButton:
				smallWidgetCount++;

				if (ImGui::Button(" ", ImVec2(bigWidth, smallHeight))) {
					widgets[j]->execute();
				}

				ImGui::SetCursorPosX(posX + 5);
				ImGui::SetCursorPosY(posY + smallHeight / 2 - (ImGui::CalcTextSize(widgets[j]->getIcon()).y / 2));

				ImGui::PushFont(iconFont);
				ImGui::Text(widgets[j]->getIcon());
				ImGui::PopFont();

				ImGui::SetCursorPosX(posX + 25);
				ImGui::SetCursorPosY(posY + smallHeight / 2 - (ImGui::CalcTextSize(widgets[j]->getTitle().c_str()).y / 2));

				ImGui::PushFont(headerFont);
				ImGui::Text(widgets[j]->getTitle().c_str());
				ImGui::PopFont();

				if (smallWidgetCount != 3) {
					posY += smallHeight + padding;
				}
				else {
					smallWidgetCount = 0;
					posY = originalY;
					posX += bigWidth + padding;
				}
				break;

			case WidgetType::Toggle:
				smallWidgetCount++;

				ImGui::PushFont(headerFont);
				ImGui::Checkbox(widgets[j]->getTitle().c_str(), widgets[j]->getBool());
				ImGui::PopFont();

				if (smallWidgetCount != 3) {
					posY += smallHeight + padding;
				}
				else {
					smallWidgetCount = 0;
					posY = originalY;
					posX += bigWidth + padding;
				}
				break;

			case WidgetType::InputFloat:
				smallWidgetCount++;

				ImGui::PushFont(headerFont);
				ImGui::PushItemWidth(bigWidth);
				ImGui::InputFloat("", widgets[j]->getFloat());
				ImGui::PopFont();

				if (smallWidgetCount != 3) {
					posY += smallHeight + padding;
				}
				else {
					smallWidgetCount = 0;
					posY = originalY;
					posX += bigWidth + padding;
				}
				break;
			}
		}

		int maxX = posX - padding;
		ImGui::SetCursorPosX(minX + (maxX - minX) / 2 - (ImGui::CalcTextSize(zones[i]->getTitle().c_str()).x / 2));
		ImGui::SetCursorPosY(132);

		ImGui::PushFont(textFont);
		ImGui::Text(zones[i]->getTitle().c_str());
		ImGui::PopFont();

		if (i != zones.size() - 1) {
			ImDrawList* drawList = ImGui::GetWindowDrawList();
			ImVec2 windowPos = ImGui::GetWindowPos();
			drawList->AddLine(ImVec2(windowPos.x + posX, windowPos.y + originalY), ImVec2(windowPos.x + posX, windowPos.y + originalY + bigHeight), 0xFF3E3E47, 2.0f);
			posX += padding;
			posY = originalY;
		}

		ImGui::PopID();
	}
}

void UIBar::verticalDraw() {
	int topOffset = 24;
	int padding = 15;
	int posY = 0;
	int leftPosX = padding;
	int leftSize = 70;
	int rightSize = ImGui::GetWindowWidth() - padding * 3 - leftSize;
	int height = 30;
	int rightPosXMin = leftPosX + leftSize + padding;
	int rightPosXMax = ImGui::GetWindowWidth() - padding;

	for (int i = 0; i < zones.size(); i++) {
		ImGui::PushID(i);
		std::vector<std::shared_ptr<UIWidget>> widgets = zones[i]->getWidgets();

		if (ImGui::CollapsingHeader(zones[i]->getTitle().c_str())) {
			posY = ImGui::GetCursorPosY();

			for (int j = 0; j < widgets.size(); j++) {
				ImGui::SetCursorPosX(leftPosX);
				ImGui::SetCursorPosY(posY + height / 2 - ImGui::CalcTextSize(widgets[j]->getTitle().c_str()).y / 2);

				ImGui::PushFont(headerFont);
				ImGui::Text(widgets[j]->getTitle().c_str());
				ImGui::PopFont();

				switch (widgets[j]->getType()) {
				case WidgetType::InputFloat:
					ImGui::SetCursorPosX(rightPosXMin);
					ImGui::SetCursorPosY(posY + 4);

					ImGui::PushItemWidth(rightSize - 8);
					ImGui::InputFloat("", widgets[j]->getFloat());
					break;

				case WidgetType::Toggle:
					ImGui::SetCursorPosX(rightPosXMax - 30);
					ImGui::SetCursorPosY(posY + 4);

					ImGui::PushFont(headerFont);
					ImGui::Checkbox(std::string("##" + std::to_string(j + 1)).c_str(), widgets[j]->getBool());
					ImGui::PopFont();
					break;
				}

				posY += height;

				ImDrawList* drawList = ImGui::GetWindowDrawList();
				ImVec2 windowPos = ImGui::GetWindowPos();
				drawList->AddLine(ImVec2(windowPos.x + rightPosXMin - padding / 2, windowPos.y + posY - ImGui::GetScrollY() - height + 6),
					ImVec2(windowPos.x + rightPosXMin - padding / 2, windowPos.y + posY - ImGui::GetScrollY() - 6),
					0xFF3E3E47, 2.0f);

				if (j != widgets.size() - 1) {
					ImDrawList* drawList = ImGui::GetWindowDrawList();
					ImVec2 windowPos = ImGui::GetWindowPos();
					drawList->AddLine(ImVec2(windowPos.x + leftPosX, windowPos.y + posY - ImGui::GetScrollY()), 
						ImVec2(windowPos.x + rightPosXMax, windowPos.y + posY - ImGui::GetScrollY()), 
						0xFF3E3E47, 2.0f);
				}
			}
		}

		ImGui::PopID();
	}
}

std::shared_ptr<int> UIBar::getWidthPtr() {
	return std::shared_ptr<int>(&width);
}

std::shared_ptr<int> UIBar::getHeightPtr() {
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