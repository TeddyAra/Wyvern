#include "SetColourCommand.h"

#include "InteractionController.h"

SetColourCommand::SetColourCommand(std::shared_ptr<InteractionController> controller, int index)
	: ICommand(controller), index(index)
{

}

void SetColourCommand::execute() {
	if (auto arg = getArg<float>()) {
		controller->setColour(*arg, index);
	}
}