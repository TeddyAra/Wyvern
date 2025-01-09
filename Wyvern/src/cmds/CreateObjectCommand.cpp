#include "CreateObjectCommand.h"

#include <iostream>

#include "InteractionController.h"
#include "Debug.h"

CreateObjectCommand::CreateObjectCommand(std::shared_ptr<InteractionController> controller)
	: ICommand(controller)
{

}

void CreateObjectCommand::execute() {
	std::shared_ptr<Transform> object = std::make_shared<Transform>();

	glm::vec3 origin = controller->getCamera()->getPosition();
	glm::vec3 direction = controller->getCamera()->getFront();
	glm::vec3 normal(0.0f, 0.0f, 0.0f);

	HitInfo info;
	if (Physics::ray(origin, direction, info, Physics::getLayerIndex("main"), maxRayLength)) {
		object->setPosition(info.hitPoint + info.normal * 0.5f);
		object->setRotation(info.object->getRotation());
		normal = info.normal;
	} else {
		object->setPosition(origin + direction * standardLength);
	}

	float moveSnap = controller->getMoveSnap();
	if (moveSnap != 0.0f) {
		glm::vec3 position = object->getPosition();
		if (normal != glm::vec3(0.0f, 0.0f, 0.0f)) {
			glm::vec3 parallel = glm::dot(position, normal) * normal;
			glm::vec3 perpendicular = position - parallel;

			for (int i = 0; i < 3; i++) {
				float remainder = fmod(perpendicular[i], moveSnap);
				if (remainder < moveSnap / 2) {
					perpendicular[i] -= remainder;
				} else {
					perpendicular[i] += -remainder + moveSnap;
				}
			}

			position = perpendicular + parallel;
		} else {
			glm::vec3 position = object->getPosition();

			for (int i = 0; i < 3; i++) {
				float remainder = fmod(position[i], moveSnap);
				if (remainder < moveSnap / 2) {
					position[i] -= remainder;
				} else {
					position[i] += -remainder + moveSnap;
				}
			}
		}

		object->setPosition(position);
	}

	controller->addObject(object);

	//std::shared_ptr<ICommand> cmd = std::make_shared<CreateObjectCommand>(controller);
	//controller->addToHistory(cmd);
}