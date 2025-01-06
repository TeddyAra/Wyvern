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

	HitInfo info;
	if (Physics::ray(origin, direction, info, Physics::getLayerIndex("main"), maxRayLength)) {
		object->setPosition(info.hitPoint + info.normal * 0.5f);
		object->setRotation(info.object->getRotation());
	} else {
		object->setPosition(origin + direction * standardLength);
	}

	controller->addObject(object);

	//std::shared_ptr<ICommand> cmd = std::make_shared<CreateObjectCommand>(controller);
	//controller->addToHistory(cmd);
}