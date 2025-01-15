#include "ToggleRotationSnapCommand.h"

#include "InteractionController.h"

ToggleRotationSnapCommand::ToggleRotationSnapCommand(std::shared_ptr<InteractionController> controller)
	: ICommand(controller) 
{

}

void ToggleRotationSnapCommand::execute() {
	if (auto arg = getArg<bool>()) {
		controller->toggleRotationSnap(*arg);
	}
}