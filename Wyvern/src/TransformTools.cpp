#include "TransformTools.h"

#include "Input.h"
#include "Physics.h"
#include "World.h"
#include "Debug.h"

TransformTools::TransformTools()
	: currentTool(Tool::Select), transforming(false)
{
	world = World::getWorld();
	camera = world->getCamera();

	moveOriginalScale = glm::vec3(0.15f, 0.15f, 1.75f);
	scaleOriginalScale = glm::vec3(0.5f, 0.5f, 0.5f);
	rotateOriginalScale = glm::vec3(0.5f, 0.5f, 0.5f);

	for (int i = 0; i < 6; i++) {
		glm::vec3 direction = directions[i];

		std::shared_ptr<Transform> tool = std::make_shared<Transform>();
		tool->setScale(moveOriginalScale);
		tool->lookAt(direction);

		tool->removeLayer(Physics::getLayerIndex("main"));
		tool->addLayer(Physics::getLayerIndex("transform"));
		if (i < 2) tool->addLayer(Physics::getLayerIndex("x"));
		else if (i < 4) tool->addLayer(Physics::getLayerIndex("y"));
		else if (i < 6) tool->addLayer(Physics::getLayerIndex("z"));

		if (i % 2 == 1) tool->addLayer(Physics::getLayerIndex("neg"));
		else tool->addLayer(Physics::getLayerIndex("pos"));

		tool->setCollider(std::make_shared<CylinderCollider>());
		tool->setColour(glm::max(direction, glm::vec3(0.0f)) + glm::abs(glm::min(direction, glm::vec3(0.0f))));

		transform.push_back(tool);
		Physics::addObject(tool);
	}
}

TransformTools::~TransformTools() {

}

void TransformTools::toggleMoveSnap(bool value) {
	moveSnapToggle = value;
}

void TransformTools::toggleRotationSnap(bool value) {
	rotationSnapToggle = value;
}

void TransformTools::setMoveSnap(float snap) { 
	moveSnap = snap;
}

void TransformTools::setRotationSnap(float snap) {
	rotationSnap = snap;
}

float TransformTools::getMoveSnap() {
	return moveSnapToggle ? moveSnap : 0;
}

float TransformTools::getRotationSnap() {
	return rotationSnapToggle ? rotationSnap : 0;
}

void TransformTools::changeTool(Tool tool) {
	currentTool = tool;
	updateScale();
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
			if (Physics::ray(rayOrigin, rayDirection, info, Physics::getLayerIndex("transform"))) {
				switch (currentTool) {
					case TransformTools::Tool::Move:
					case TransformTools::Tool::Scale:
					{
						transforming = true;

						originalPos = world->getSelected()[0]->getPosition();
						originalScale = world->getSelected()[0]->getScale();

						if (info.object->checkLayer(Physics::getLayerIndex("x"))) {
							planeDirection = world->getSelected()[0]->getRight();
							localDirection = glm::vec3(1.0f, 0.0f, 0.0f);
						} else if (info.object->checkLayer(Physics::getLayerIndex("y"))) {
							planeDirection = world->getSelected()[0]->getUp();
							localDirection = glm::vec3(0.0f, 1.0f, 0.0f);
						} else if (info.object->checkLayer(Physics::getLayerIndex("z"))) {
							planeDirection = world->getSelected()[0]->getFront();
							localDirection = glm::vec3(0.0f, 0.0f, 1.0f);
						}

						if (info.object->checkLayer(Physics::getLayerIndex("neg"))) {
							localDirection *= -1.0f;
						}

						float originDistance = glm::dot(planeDirection, info.hitPoint - world->getSelected()[0]->getPosition());
						planeOrigin = world->getSelected()[0]->getPosition() + planeDirection * originDistance;
						return;
					}

					case TransformTools::Tool::Rotate:
					{
						transforming = true;

						if (info.object->checkLayer(Physics::getLayerIndex("x"))) {
							planeNormal = world->getSelected()[0]->getUp();
						} else if (info.object->checkLayer(Physics::getLayerIndex("y"))) {
							planeNormal = world->getSelected()[0]->getFront();
						} else if (info.object->checkLayer(Physics::getLayerIndex("z"))) {
							planeNormal = world->getSelected()[0]->getRight();
						}

						planeOrigin = world->getSelected()[0]->getPosition();

						HitInfo info;
						if (Physics::rayPlane(rayOrigin, rayDirection, planeOrigin, planeNormal, info)) {
							originalDirection = glm::normalize(info.hitPoint - planeOrigin);
						}

						originalRotation = world->getSelected()[0]->getEulerRotation();
						return;
					}
				}
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

		// Calculate viewport and mouse variables
		glm::vec2 viewportPos = world->getViewportPos();
		glm::vec2 viewportSize = world->getViewportSize();
		glm::vec2 mousePos = Input::getMousePosition() - viewportPos;

		// Calculate ray origin and direction
		glm::vec3 rayOrigin = camera->getPosition();
		glm::vec3 rayDirection = camera->getModelMatrix() * glm::vec4(Input::posToRayDirection(mousePos, viewportSize, camera->getFov()), 0.0f);
		rayDirection = glm::normalize(rayDirection);

		if (currentTool == Tool::Move || currentTool == Tool::Scale) {
			float cameraDistance = glm::dot(planeDirection, camera->getPosition() - world->getSelected()[0]->getPosition());
			glm::vec3 closestPoint = world->getSelected()[0]->getPosition() + planeDirection * cameraDistance;
			planeNormal = glm::normalize(camera->getPosition() - closestPoint);

			HitInfo info;
			if (Physics::rayPlane(rayOrigin, rayDirection, planeOrigin, planeNormal, info)) {
				float translation = glm::dot(planeDirection, info.hitPoint - planeOrigin);

				// Snapping
				if (moveSnap != 0.0f && moveSnapToggle) {
					float remainder = fmod(translation, moveSnap);
					if (remainder < moveSnap / 2) {
						translation -= remainder;
					} else {
						translation += -remainder + moveSnap;
					}
				}

				if (currentTool == Tool::Scale) {
					world->getSelected()[0]->setScale(originalScale + localDirection * translation);
					translation *= 0.5f;
				}

				world->getSelected()[0]->setPosition(originalPos + planeDirection * translation);
				selectionOrigin = world->getSelected()[0]->getPosition();
				selectionSize = world->getSelected()[0]->getScale() * 0.5f;
			}
		} else if (currentTool == Tool::Rotate) {
			HitInfo info;
			if (Physics::rayPlane(rayOrigin, rayDirection, planeOrigin, planeNormal, info)) {
				glm::vec3 currentDirection = glm::normalize(info.hitPoint - planeOrigin);
				float dot = glm::clamp(glm::dot(originalDirection, currentDirection), -1.0f, 1.0f);

				glm::vec3 cross = glm::cross(originalDirection, currentDirection);
				float sign = glm::dot(cross, planeNormal) < 0 ? -1.0f : 1.0f;

				float angle = glm::degrees(acos(dot)) * sign;

				// Snapping
				if (rotationSnap != 0.0f && rotationSnapToggle) {
					float remainder = fmod(angle, rotationSnap);
					if (remainder < rotationSnap / 2) {
						angle -= remainder;
					} else {
						angle += -remainder + moveSnap;
					}
				}

				world->getSelected()[0]->setRotation(originalRotation);
				world->getSelected()[0]->rotateAroundAxis(planeNormal, angle);
			}
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

	float distance = glm::length(world->getCamera()->getPosition() - world->getSelected()[0]->getPosition());
	for (int i = 0; i < transform.size(); i++) {
		
		glm::vec3 toolOriginalScale(1.0f, 1.0f, 1.0f);
		switch (currentTool) {
		case TransformTools::Tool::Move:
			toolOriginalScale = moveOriginalScale;
			break;
		case TransformTools::Tool::Scale:
			toolOriginalScale = scaleOriginalScale;
			break;
		case TransformTools::Tool::Rotate:
			toolOriginalScale = rotateOriginalScale;
			break;
		}

		glm::vec3 scale = toolOriginalScale * scaleFactor * distance;
		transform[i]->setScale(scale);

		float objectSize = 1.0f;
		if (currentTool == TransformTools::Tool::Rotate) {
			objectSize = glm::max(glm::max(selectionSize.x, selectionSize.y), selectionSize.z);
		} else {
			if (i < 2) objectSize = selectionSize.x;
			else if (i < 4) objectSize = selectionSize.y;
			else if (i < 6) objectSize = selectionSize.z;
		}

		float displacement = objectSize + scale.z * 0.75f;

		transform[i]->setPosition(selectionOrigin);
		transform[i]->lookAt(selectionOrigin + directions[i] * glm::inverse(world->getSelected()[0]->getRotation()));
		transform[i]->translate(transform[i]->getFront() * displacement);
	}
}