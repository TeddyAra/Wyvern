#include "TransformTools.h"

#include "Input.h"
#include "Physics.h"
#include "World.h"

TransformTools::TransformTools()
: currentTool(Tool::Select), transforming(false)
{
	world = World::getWorld();
	camera = world->getCamera();

	originalScale = glm::vec3(0.15f, 0.15f, 1.75f);

	for (const glm::vec3& direction : directions) {
		std::shared_ptr<Transform> tool = std::make_shared<Transform>();
		tool->setScale(originalScale);
		tool->lookAt(direction);

		tool->removeLayer(Physics::getLayerIndex("main"));
		tool->addLayer(Physics::getLayerIndex("transform"));
		tool->addLayer(Physics::getLayerIndex("move"));
		tool->setCollider(std::make_shared<CylinderCollider>());
		tool->setColour(glm::max(direction, glm::vec3(0.0f)) + glm::abs(glm::min(direction, glm::vec3(0.0f))));

		transform.push_back(tool);
		Physics::addObject(tool);
	}
}

TransformTools::~TransformTools() {

}

void TransformTools::changeTool(Tool tool) {
	currentTool = tool;
}

TransformTools::Tool TransformTools::getTool() {
	return currentTool;
}

void TransformTools::checkTool() {
	updateScale();

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
			switch (currentTool) {
				case 1:
					if (Physics::ray(rayOrigin, rayDirection, info, Physics::getLayerIndex("move"))) {
						transforming = true;

						originalPos = world->getSelected()[0]->getPosition();
						planeDirection = info.object->getFront();
						float originDistance = glm::dot(planeDirection, info.hitPoint - world->getSelected()[0]->getPosition());
						planeOrigin = world->getSelected()[0]->getPosition() + planeDirection * originDistance;
						return;
					}
					break;
				case 2:
					if (Physics::ray(rayOrigin, rayDirection, info, Physics::getLayerIndex("scale"))) {
						transforming = true;
						return;
					}
					break;
				case 3:
					if (Physics::ray(rayOrigin, rayDirection, info, Physics::getLayerIndex("rotate"))) {
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
			world->getSelected().push_back(info.object);
			if (world->getSelected().size() == 1) {
				selectionOrigin = info.object->getPosition() + info.object->getOrigin();
				selectionSize = info.object->getScale() * 0.5f;
			}
		}
	} 
	
	if (transforming) {
		if (!Input::getMouse(0)) {
			transforming = false;
			return;
		}

		// Calculate plane normal
		float cameraDistance = glm::dot(planeDirection, camera->getPosition() - world->getSelected()[0]->getPosition());
		glm::vec3 closestPoint = world->getSelected()[0]->getPosition() + planeDirection * cameraDistance;
		glm::vec3 planeNormal = glm::normalize(camera->getPosition() - closestPoint);

		// Calculate viewport and mouse variables
		glm::vec2 viewportPos = world->getViewportPos();
		glm::vec2 viewportSize = world->getViewportSize();
		glm::vec2 mousePos = Input::getMousePosition() - viewportPos;

		// Calculate ray origin and direction
		glm::vec3 rayOrigin = camera->getPosition();
		glm::vec3 rayDirection = camera->getModelMatrix() * glm::vec4(Input::posToRayDirection(mousePos, viewportSize, camera->getFov()), 0.0f);
		rayDirection = glm::normalize(rayDirection);

		HitInfo info;
		if (Physics::rayPlane(rayOrigin, rayDirection, planeOrigin, planeNormal, info)) {
			float translation = glm::dot(planeDirection, info.hitPoint - planeOrigin);
			world->getSelected()[0]->setPosition(originalPos + planeDirection * translation);
			selectionOrigin = world->getSelected()[0]->getPosition();
		}
	}
}

std::vector<std::shared_ptr<Transform>>& TransformTools::getTransformTools() {
	return transform;
}

void TransformTools::updateScale() {
	if (world->getSelected().size() == 0) {
		for (int i = 0; i < transform.size(); i++) {
			transform[i]->setPosition(0.0f, 0.0f, 0.0f);
			transform[i]->setScale(0.0f, 0.0f, 0.0f);
		}
		return;
	}

	const float scaleFactor = 0.15f;

	for (int i = 0; i < transform.size(); i++) {
		float distance = glm::length(world->getCamera()->getPosition() - transform[i]->getPosition());
		glm::vec3 scale = originalScale * scaleFactor * distance;
		transform[i]->setScale(scale);

		float objectSize = 1.0f;
		if (i < 2) objectSize = selectionSize.x;
		else if (i < 4) objectSize = selectionSize.y;
		else if (i < 6) objectSize = selectionSize.z;

		float displacement = objectSize + scale.z * 0.75f;

		transform[i]->setPosition(selectionOrigin);
		transform[i]->lookAt(selectionOrigin + directions[i] * glm::inverse(world->getSelected()[0]->getRotation()));
		transform[i]->translate(transform[i]->getFront() * displacement);
	}
}