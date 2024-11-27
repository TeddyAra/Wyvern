#include "DebugCommand.h"

#include <iostream>

#include "InteractionController.h"

DebugCommand::DebugCommand(std::shared_ptr<InteractionController> controller)
	: ICommand(controller) 
{

}

void DebugCommand::execute() {
	if (args.size() == 0) {
		std::cout << "No arguments given to debug command" << std::endl;
		return;
	}

	bool cast = false;
	float debug = 0.0f;
	for (std::any arg : args) {
		if (arg.type() == typeid(float)) {
			debug = std::any_cast<float>(arg);
			cast = true;
			break;
		}
	}

	if (!cast) {
		std::cout << "Wrong arguments given to debug command" << std::endl;
		return;
	}

	controller->setDebug(debug);
	std::shared_ptr<ICommand> cmd = std::make_shared<DebugCommand>(controller);
	cmd->setArgs(args);
	controller->addToHistory(cmd);
}