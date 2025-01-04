#include "SwitchToolCommand.h"

#include <iostream>

#include "InteractionController.h"

SwitchToolCommand::SwitchToolCommand(std::shared_ptr<InteractionController> controller, TransformTools::Tool tool)
	: ICommand(controller), tool(tool)
{

}

void SwitchToolCommand::execute() {
	controller->changeTool(tool);
}