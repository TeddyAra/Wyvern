#include "UIBarList.h"

void UIBarList::draw() {
	rightSize = ImGui::GetWindowWidth() - padding * 3 - leftSize;
	rightPosXMax = ImGui::GetWindowWidth() - padding;
	widgetIndex = 0;

	for (int i = 0; i < zones.size(); i++) {
		std::vector<std::shared_ptr<UIWidget>> widgets = zones[i]->getWidgets();

		if (ImGui::CollapsingHeader(zones[i]->getTitle().c_str())) {
			posY = ImGui::GetCursorPosY();

			for (int j = 0; j < widgets.size(); j++) {
				ImGui::PushID(widgetIndex);

				ImGui::SetCursorPosX(leftPosX);
				ImGui::SetCursorPosY(posY + height / 2 - ImGui::CalcTextSize(widgets[j]->getTitle().c_str()).y / 2);

				ImGui::PushFont(headerFont);
				ImGui::Text(widgets[j]->getTitle().c_str());
				ImGui::PopFont();

				switch (widgets[j]->getType()) {
				case WidgetType::InputFloat:
					drawInputFloat(widgets, j);
					break;

				case WidgetType::Toggle:
					drawToggle(widgets, j);
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

				ImGui::PopID();
				widgetIndex++;
			}
		}
	}
}

void UIBarList::drawBigButton(std::vector<std::shared_ptr<UIWidget>> widgets, int index) {

}

void UIBarList::drawSmallButton(std::vector<std::shared_ptr<UIWidget>> widgets, int index) {

}

void UIBarList::drawToggle(std::vector<std::shared_ptr<UIWidget>> widgets, int index) {
	ImGui::SetCursorPosX(rightPosXMax - 30);
	ImGui::SetCursorPosY(posY + 4);

	ImGui::PushFont(headerFont);
	ImGui::Checkbox(std::string("##" + std::to_string(index + 1)).c_str(), widgets[index]->getBool());
	ImGui::PopFont();
}

void UIBarList::drawInputFloat(std::vector<std::shared_ptr<UIWidget>> widgets, int index) {
	ImGui::SetCursorPosX(rightPosXMin);
	ImGui::SetCursorPosY(posY + 4);

	ImGui::PushItemWidth(rightSize - 8);
	ImGui::InputFloat("", widgets[index]->getFloat());
}