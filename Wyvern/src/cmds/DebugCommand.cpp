#include "DebugCommand.h"

#include <iostream>

#include "InteractionController.h"

DebugCommand::DebugCommand(std::shared_ptr<InteractionController> controller)
	: ICommand(controller) 
{

}

void DebugCommand::execute() {
	if (auto arg = getArg<float>()) {
		controller->setDebug(*arg);
		std::shared_ptr<ICommand> cmd = std::make_shared<DebugCommand>(controller);
		cmd->setArgs(args);
		controller->addToHistory(cmd);
	}
}