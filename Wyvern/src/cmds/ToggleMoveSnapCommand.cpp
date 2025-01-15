#include "ToggleMoveSnapCommand.h"

#include "InteractionController.h"

ToggleMoveSnapCommand::ToggleMoveSnapCommand(std::shared_ptr<InteractionController> controller)
	: ICommand(controller) 
{

}

void ToggleMoveSnapCommand::execute() {
	if (auto arg = getArg<bool>()) {
		controller->toggleMoveSnap(*arg);
	}
}