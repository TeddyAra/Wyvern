#include "Viewport.h"

#include <iostream>

void Viewport::draw() {
	ImVec2 viewportSize = ImGui::GetWindowSize();
	ImVec2 viewportPos = ImGui::GetWindowPos();

	int windowWidth, windowHeight;
	glfwGetWindowSize(window, &windowWidth, &windowHeight);
	viewportPos.y = (viewportPos.y + viewportSize.y - windowHeight) * -1;
	glViewport(viewportPos.x, viewportPos.y, viewportSize.x, viewportSize.y);

	renderer->render();
	//glfwSwapBuffers(window);
	//glfwPollEvents();
}