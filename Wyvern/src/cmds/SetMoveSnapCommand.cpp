#include "CommandTemplate.h"

#include "InteractionController.h"
#include "SetMoveSnapCommand.h"

SetMoveSnapCommand::SetMoveSnapCommand(std::shared_ptr<InteractionController> controller)
	: ICommand(controller) 
{

}

void SetMoveSnapCommand::execute() {
	if (auto arg = getArg<float>()) {
		controller->setMoveSnap(*arg);
	}
}