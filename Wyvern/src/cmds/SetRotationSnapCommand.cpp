#include "CommandTemplate.h"

#include "InteractionController.h"
#include "SetRotationSnapCommand.h"

SetRotationSnapCommand::SetRotationSnapCommand(std::shared_ptr<InteractionController> controller)
	: ICommand(controller) 
{

}

void SetRotationSnapCommand::execute() {
	if (auto arg = getArg<float>()) {
		controller->setRotationSnap(*arg);
	}
}