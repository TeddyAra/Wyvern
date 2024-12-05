#include "Viewport.h"

#include <iostream>

void Viewport::draw() {
	int displayWidth, displayHeight;
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
	}
}