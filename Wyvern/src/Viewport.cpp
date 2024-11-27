#include "Viewport.h"

#include <iostream>

void Viewport::draw() {
	int displayWidth, displayHeight;
	glfwGetFramebufferSize(window, &displayWidth, &displayHeight);
	glViewport(0, 0, displayWidth, displayHeight);

	renderer->render();
	//glfwSwapBuffers(window);
	//glfwPollEvents();
}