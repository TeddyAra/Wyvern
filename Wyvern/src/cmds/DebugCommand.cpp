#include "cmds/DebugCommand.h"

#include <iostream>

DebugCommand::DebugCommand(std::shared_ptr<InteractionController> controller)
	: ICommand(controller) {

}

void DebugCommand::execute() {
	std::cout << controller->getSelected() << std::endl;
}