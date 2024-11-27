#include "UIBarMenu.h"

#include <iostream>

void UIBarMenu::draw() {
	widgetIndex = 0;
	posX = padding;
	posY = originalY;

	for (int i = 0; i < zones.size(); i++) {
		std::vector<std::shared_ptr<UIWidget>> widgets = zones[i]->getWidgets();
		minX = posX;

		for (int j = 0; j < widgets.size(); j++) {
			ImGui::PushID(widgetIndex);

			ImGui::SetCursorPosX(posX);
			ImGui::SetCursorPosY(posY);

			switch (widgets[j]->getType()) {
			case WidgetType::LargeButton:
				drawBigButton(widgets, j);
				break;

			case WidgetType::SmallButton:
				drawSmallButton(widgets, j);
				break;

			case WidgetType::Toggle:
				drawToggle(widgets, j);
				break;

			case WidgetType::InputFloat:
				drawInputFloat(widgets, j);
				break;
			}

			ImGui::PopID();
			widgetIndex++;
		}

		if (smallWidgetCount != 0) {
			smallWidgetCount = 0;
			posX += bigWidth + padding;
		}
		int maxX = posX - padding;

		ImGui::SetCursorPosX(minX + (maxX - minX) / 2 - (ImGui::CalcTextSize(zones[i]->getTitle().c_str()).x / 2));
		ImGui::SetCursorPosY(126);

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
	}
}

void UIBarMenu::drawBigButton(std::vector<std::shared_ptr<UIWidget>> widgets, int index) {
	if (smallWidgetCount != 0) {
		posY = originalY;
		posX += bigWidth + padding;
		smallWidgetCount = 0;

		ImGui::SetCursorPosX(posX);
		ImGui::SetCursorPosY(posY);
	}

	ImGui::PushFont(iconFont);
	ImGui::SetWindowFontScale(1.5f);
	if (ImGui::Button(widgets[index]->getIcon(), ImVec2(60, bigHeight))) {
		widgets[index]->execute();
	}
	ImGui::SetWindowFontScale(1.0f);
	ImGui::PopFont();

	ImGui::SetCursorPosX(posX + smallWidth / 2 - (ImGui::CalcTextSize(widgets[index]->getTitle().c_str()).x / 2));
	ImGui::SetCursorPosY(posY + bigHeight - textHeight * 2);

	ImGui::PushFont(headerFont);
	ImGui::Text(widgets[index]->getTitle().c_str(), ImVec2(smallWidth, textHeight));
	ImGui::PopFont();

	posX += smallWidth + padding;
}

void UIBarMenu::drawSmallButton(std::vector<std::shared_ptr<UIWidget>> widgets, int index) {
	smallWidgetCount++;

	if (ImGui::Button(" ", ImVec2(bigWidth, smallHeight))) {
		widgets[index]->execute();
	}

	ImGui::SetCursorPosX(posX + 5);
	ImGui::SetCursorPosY(posY + smallHeight / 2 - (ImGui::CalcTextSize(widgets[index]->getIcon()).y / 2));

	ImGui::PushFont(iconFont);
	ImGui::Text(widgets[index]->getIcon());
	ImGui::PopFont();

	ImGui::SetCursorPosX(posX + 25);
	ImGui::SetCursorPosY(posY + smallHeight / 2 - (ImGui::CalcTextSize(widgets[index]->getTitle().c_str()).y / 2));

	ImGui::PushFont(headerFont);
	ImGui::Text(widgets[index]->getTitle().c_str());
	ImGui::PopFont();

	if (smallWidgetCount != 3) {
		posY += smallHeight + padding;
	} else {
		smallWidgetCount = 0;
		posY = originalY;
		posX += bigWidth + padding;
	}
}

void UIBarMenu::drawToggle(std::vector<std::shared_ptr<UIWidget>> widgets, int index) {
	smallWidgetCount++;

	ImGui::PushFont(headerFont);
	ImGui::Checkbox(widgets[index]->getTitle().c_str(), widgets[index]->getBool());
	ImGui::PopFont();

	if (smallWidgetCount != 3) {
		posY += smallHeight + padding;
	} else {
		smallWidgetCount = 0;
		posY = originalY;
		posX += bigWidth + padding;
	}
}

void UIBarMenu::drawInputFloat(std::vector<std::shared_ptr<UIWidget>> widgets, int index) {
	smallWidgetCount++;

	ImGui::PushFont(headerFont);
	ImGui::PushItemWidth(bigWidth);
	if (ImGui::InputFloat("", widgets[index]->getFloat(), 0.0f, 0.0f, -1, ImGuiInputTextFlags_EnterReturnsTrue)) {
		std::vector<std::any> args { *widgets[index]->getFloat() };
		widgets[index]->setArgs(args);
		widgets[index]->execute();
	}
	ImGui::PopFont();

	if (smallWidgetCount != 3) {
		posY += smallHeight + padding;
	} else {
		smallWidgetCount = 0;
		posY = originalY;
		posX += bigWidth + padding;
	}
}