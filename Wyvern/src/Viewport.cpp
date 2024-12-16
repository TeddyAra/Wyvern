#include "Viewport.h"

#include <iostream>

void Viewport::draw() {
	ImVec2 viewportPos = ImVec2(ImGui::GetWindowPos().x + ImGui::GetCursorPosX(), ImGui::GetWindowPos().y + ImGui::GetCursorPosY());

	if (!resized) {
		ImVec2 region = ImGui::GetContentRegionAvail();
		renderer->updateSize(viewportPos.x, viewportPos.y, region.x, region.y);
		resized = true;
	}

	renderer->render();
	ImGui::Image((intptr_t)renderer->getTex(), renderer->getSize());
}

void Viewport::clear() {
	renderer->clear();
}

void Viewport::resize() {
	resized = false;
}