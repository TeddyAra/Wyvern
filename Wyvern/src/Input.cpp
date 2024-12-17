#include "Input.h"

GLFWwindow* Input::window = nullptr;
std::map<int, bool> Input::keyMemory;
std::map<int, bool> Input::mouseMemory;
glm::vec2 Input::mousePosition;
glm::vec2 Input::lastMousePosition;
bool Input::firstMouse = true;

void Input::setWindow(GLFWwindow* window) {
	Input::window = window;
	glfwSetCursorPosCallback(window, Input::mouseCallback);
}

void Input::update() {
	// Update the map to hold the last frame's key and mouse information
	std::map<int, bool>::iterator itKey;
	for (itKey = keyMemory.begin(); itKey != keyMemory.end(); itKey++) {
		keyMemory[itKey->first] = getKey(itKey->first);
	}

	std::map<int, bool>::iterator itMouse;
	for (itMouse = mouseMemory.begin(); itMouse != mouseMemory.end(); itMouse++) {
		mouseMemory[itMouse->first] = getMouse(itMouse->first);
	}

	lastMousePosition = mousePosition;
}

bool Input::getKey(int key) {
	return (glfwGetKey(window, key) == GLFW_PRESS);
}

bool Input::getKeyDown(int key) {
	if (keyMemory.find(key) != keyMemory.end()) {
		return (!keyMemory[key] && glfwGetKey(window, key) == GLFW_PRESS);
	} else {
		keyMemory[key] = false;
		return getKey(key);
	}
}

bool Input::getKeyUp(int key) {
	if (keyMemory.find(key) != keyMemory.end()) {
		return (keyMemory[key] && glfwGetKey(window, key) != GLFW_PRESS);
	} else {
		keyMemory[key] = false;
		return getKey(key);
	}
}

glm::vec2 Input::getMousePosition() {
	return mousePosition;
}

glm::vec2 Input::getDeltaMousePosition() {
	return mousePosition - lastMousePosition;
}

bool Input::getMouse(int button) {
	return (glfwGetMouseButton(window, button) == GLFW_PRESS);
}

bool Input::getMouseDown(int button) {
	if (mouseMemory.find(button) != mouseMemory.end()) {
		return (!mouseMemory[button] && glfwGetMouseButton(window, button) == GLFW_PRESS);
	} else {
		mouseMemory[button] = false;
		return getMouse(button);
	}
}

bool Input::getMouseUp(int button) {
	if (mouseMemory.find(button) != mouseMemory.end()) {
		return (mouseMemory[button] && glfwGetMouseButton(window, button) != GLFW_PRESS);
	} else {
		mouseMemory[button] = false;
		return getMouse(button);
	}
}

void Input::mouseCallback(GLFWwindow* window, double xpos, double ypos) {
	// If this is called for the first time, have mousePosition set to the current mouse position
	if (firstMouse) {
		mousePosition = glm::vec2(xpos, ypos);
		firstMouse = false;
	}

	// Update current mouse position
	mousePosition = glm::vec2(xpos, ypos);
}

glm::vec3 Input::posToRayDirection(glm::vec2 pos, glm::vec2 viewportSize, float fov) {
	// TODO: Quick fix, flipped mouseX and mouseY to be from 1 to -1 instead of from -1 to 1
	float mouseX = (pos.x / viewportSize.x) * -2.0f + 1.0f;
	float mouseY = (pos.y / viewportSize.y) * -2.0f + 1.0f;

	float ratio = viewportSize.x / viewportSize.y;
	float tanHalfFovY = glm::tan(glm::radians(fov) / 2.0f);

	glm::vec3 rayDirection = mouseX * ratio * tanHalfFovY * glm::vec3(1.0f, 0.0f, 0.0f)
		+ mouseY * tanHalfFovY * glm::vec3(0.0f, 1.0f, 0.0f)
		+ glm::vec3(0.0f, 0.0f, 1.0f);

	return glm::normalize(rayDirection);
}

glm::vec3 Input::posToRayDirection(float posX, float posY, glm::vec2 viewportSize, float fov) {
	return Input::posToRayDirection(glm::vec2(posX, posY), viewportSize, fov);
}

glm::vec3 Input::posToRayDirection(glm::vec2 pos, float viewportWidth, float viewportHeight, float fov) {
	return Input::posToRayDirection(pos, glm::vec2(viewportWidth, viewportHeight), fov);
}

glm::vec3 Input::posToRayDirection(float posX, float posY, float viewportWidth, float viewportHeight, float fov) {
	return Input::posToRayDirection(glm::vec2(posX, posY), glm::vec2(viewportWidth, viewportHeight), fov);
}

glm::vec3 Input::getRelativeDirection(glm::mat4 viewMatrix, glm::vec3 direction) {
	glm::mat4 inverseMatrix = glm::inverse(viewMatrix);
	glm::vec4 transformedRay = inverseMatrix * glm::vec4(direction, 0.0f);
	return glm::vec3(transformedRay);
}

bool Input::isPosInsideRect(glm::vec2 pos, glm::vec2 rectPos, glm::vec2 rectSize) {
	bool withinX = pos.x >= rectPos.x && pos.x <= rectPos.x + rectSize.x;
	bool withinY = pos.y >= rectPos.y && pos.y <= rectPos.y + rectSize.y;

	return withinX && withinY;
}

bool Input::isPosInsideRect(float posX, float posY, glm::vec2 rectPos, glm::vec2 rectSize) {
	return Input::isPosInsideRect(glm::vec2(posX, posY), rectPos, rectSize);
}

bool Input::isPosInsideRect(glm::vec2 pos, float rectPosX, float rectPosY, glm::vec2 rectSize) {
	return Input::isPosInsideRect(pos, glm::vec2(rectPosX, rectPosY), rectSize);
}

bool Input::isPosInsideRect(float posX, float posY, float rectPosX, float rectPosY, glm::vec2 rectSize) {
	return Input::isPosInsideRect(glm::vec2(posX, posY), glm::vec2(rectPosX, rectPosY), rectSize);
}

bool Input::isPosInsideRect(glm::vec2 pos, glm::vec2 rectPos, float rectWidth, float rectHeight) {
	return Input::isPosInsideRect(pos, rectPos, glm::vec2(rectWidth, rectHeight));
}

bool Input::isPosInsideRect(float posX, float posY, glm::vec2 rectPos, float rectWidth, float rectHeight) {
	return Input::isPosInsideRect(glm::vec2(posX, posY), rectPos, glm::vec2(rectWidth, rectHeight));
}

bool Input::isPosInsideRect(glm::vec2 pos, float rectPosX, float rectPosY, float rectWidth, float rectHeight) {
	return Input::isPosInsideRect(pos, glm::vec2(rectPosX, rectPosY), glm::vec2(rectWidth, rectHeight));
}

bool Input::isPosInsideRect(float posX, float posY, float rectPosX, float rectPosY, float rectWidth, float rectHeight) {
	return Input::isPosInsideRect(glm::vec2(posX, posY), glm::vec2(rectPosX, rectPosY), glm::vec2(rectWidth, rectHeight));
}