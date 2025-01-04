#include "Viewport.h"

Viewport* Viewport::viewportInstance;

void Viewport::draw() {
	ImVec2 viewportPos = ImVec2(ImGui::GetWindowPos().x + ImGui::GetCursorPosX(), ImGui::GetWindowPos().y + ImGui::GetCursorPosY());

	if (!resized) {
		ImVec2 region = ImGui::GetContentRegionAvail();
		renderer->updateSize(viewportPos.x, viewportPos.y, region.x, region.y);
		resized = true;
	}

	renderer->render();
	ImGui::Image((intptr_t)renderer->getFramebufferTexture(), renderer->getSize());
}

void Viewport::clear() {
	renderer->clear();
}

void Viewport::resize() {
	resized = false;
}

void Viewport::sizeCallback(GLFWwindow* window, int width, int height) {
		Viewport::getViewport()->resize();
}

std::shared_ptr<Renderer> Viewport::getRenderer() {
	return renderer;
}

Viewport* Viewport::getViewport() {
	return viewportInstance;
}