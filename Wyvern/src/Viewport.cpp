#include "Viewport.h"

#include <iostream>

void Viewport::draw() {
	/*int displayWidth, displayHeight;
	glfwGetFramebufferSize(window, &displayWidth, &displayHeight);
	
	int windowWidth, windowHeight;
	glfwGetWindowSize(window, &windowWidth, &windowHeight);
	
	int windowPosX, windowPosY;
	glfwGetWindowPos(window, &windowPosX, &windowPosY);
	
	ImVec2 pos = ImVec2(posX - windowPosX, (posY - windowPosY + height - windowHeight) * -1);
	glViewport(pos.x, pos.y, width, height);

	renderer->render();

	ImGuiIO& io = ImGui::GetIO();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
		ImGui::UpdatePlatformWindows();
		glfwMakeContextCurrent(window);
	}*/

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