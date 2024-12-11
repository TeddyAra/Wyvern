#include "Viewport.h"

#include <iostream>

void Viewport::draw() {
	if (!resized) {
		ImVec2 region = ImGui::GetContentRegionAvail();
		renderer->updateSize(region.x, region.y);
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