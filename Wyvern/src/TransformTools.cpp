#include "TransformTools.h"

#include "Input.h"
#include "Physics.h"
#include "World.h"

TransformTools::TransformTools()
: currentTool(Tool::Select), transforming(false)
{
	world = World::getWorld();
	camera = world->getCamera();
}

TransformTools::~TransformTools() {

}

void TransformTools::changeTool(Tool tool) {
	std::cout << "Changed tool to " << std::to_string(tool) << std::endl;
	currentTool = tool;
}

void TransformTools::checkTool() {
	if (!transforming && Input::getMouseDown(0)) {
		glm::vec2 viewportPos = world->getViewportPos();
		glm::vec2 viewportSize = world->getViewportSize();

		if (!Input::isPosInsideRect(Input::getMousePosition(), viewportPos, viewportSize)) {
			return;
		}

		glm::vec2 mousePos = Input::getMousePosition() - viewportPos;

		glm::vec3 rayOrigin = camera->getPosition();
		glm::vec3 rayDirection = camera->getModelMatrix() * glm::vec4(Input::posToRayDirection(mousePos, viewportSize, camera->getFov()), 0.0f);
		rayDirection = glm::normalize(rayDirection);

		HitInfo info;
		if (world->getSelected().size() != 0) {
			std::cout << "Check " << currentTool << std::endl;
			switch (currentTool) {
				case 1:
					if (Physics::ray(rayOrigin, rayDirection, info, Physics::getLayerIndex("move"))) {
						std::cout << "Move transform" << std::endl;
						transforming = true;
						return;
					}
					break;
				case 2:
					if (Physics::ray(rayOrigin, rayDirection, info, Physics::getLayerIndex("scale"))) {
						std::cout << "Scale transform" << std::endl;
						transforming = true;
						return;
					}
					break;
				case 3:
					if (Physics::ray(rayOrigin, rayDirection, info, Physics::getLayerIndex("rotate"))) {
						std::cout << "Rotate transform" << std::endl;
						transforming = true;
						return;
					}
					break;
			}
		}

		// Clear selection if left control isn't held
		if (!Input::getKey(GLFW_KEY_LEFT_CONTROL)) {
			world->getSelected().clear();
		}

		if (Physics::ray(rayOrigin, rayDirection, info, Physics::getLayerIndex("main"))) {
			std::cout << "Main" << std::endl;
			world->getSelected().push_back(info.object);
		}
	} else if (transforming) {
		std::cout << "Transforming" << std::endl;

		if (!Input::getMouse(0)) {
			transforming = false;
		}
	}
}