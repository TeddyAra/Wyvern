#pragma once

#include <string>
#include <iostream>
#include <map>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Input {
public:
	Input() = delete;

	static void setWindow(GLFWwindow* window);
	static void update();

	// Keys
	static bool getKey(int key);
	static bool getKeyDown(int key);
	static bool getKeyUp(int key);

	// Mouse
	static glm::vec2 getMousePosition();
	static glm::vec2 getDeltaMousePosition();

	static bool getMouse(int button);
	static bool getMouseDown(int button);
	static bool getMouseUp(int button);

	static void mouseCallback(GLFWwindow* window, double xPos, double yPos);

	// Position calculations
	static glm::vec3 posToRayDirection(glm::vec2 pos, glm::vec2 viewportSize, float fov);
	static glm::vec3 posToRayDirection(float posX, float posY, glm::vec2 viewportSize, float fov);
	static glm::vec3 posToRayDirection(glm::vec2 pos, float viewportWidth, float viewportHeight, float fov);
	static glm::vec3 posToRayDirection(float posX, float posY, float viewportWidth, float viewportHeight, float fov);

	static glm::vec3 getRelativeDirection(glm::mat4 viewMatrix, glm::vec3 direction);

	static bool isPosInsideRect(glm::vec2 pos, glm::vec2 rectPos, glm::vec2 rectSize);
	static bool isPosInsideRect(float posX, float posY, glm::vec2 rectPos, glm::vec2 rectSize);
	static bool isPosInsideRect(glm::vec2 pos, float rectPosX, float rectPosY, glm::vec2 rectSize);
	static bool isPosInsideRect(float posX, float posY, float rectPosX, float rectPosY, glm::vec2 rectSize);
	static bool isPosInsideRect(glm::vec2 pos, glm::vec2 rectPos, float rectWidth, float rectHeight);
	static bool isPosInsideRect(float posX, float posY, glm::vec2 rectPos, float rectWidth, float rectHeight);
	static bool isPosInsideRect(glm::vec2 pos, float rectPosX, float rectPosY, float rectWidth, float rectHeight);
	static bool isPosInsideRect(float posX, float posY, float rectPosX, float rectPosY, float rectWidth, float rectHeight);

private:
	static std::map<int, bool> keyMemory;
	static std::map<int, bool> mouseMemory;
	static GLFWwindow* window;

	static glm::vec2 mousePosition;
	static glm::vec2 lastMousePosition;

	static bool firstMouse;
};