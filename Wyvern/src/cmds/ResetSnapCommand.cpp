#include "ResetSnapCommand.h"

#include "InteractionController.h"

ResetSnapCommand::ResetSnapCommand(std::shared_ptr<InteractionController> controller)
	: ICommand(controller) 
{

}

void ResetSnapCommand::execute() {
	float moveSnap = controller->getMoveSnap();
	for (std::shared_ptr<Transform>& object : controller->getSelected()) {
		object->snapPosition(moveSnap);
	}
}