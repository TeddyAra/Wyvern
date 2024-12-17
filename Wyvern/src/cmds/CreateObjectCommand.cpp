#include "CreateObjectCommand.h"

#include <iostream>

#include "InteractionController.h"

CreateObjectCommand::CreateObjectCommand(std::shared_ptr<InteractionController> controller)
	: ICommand(controller)
{

}

void CreateObjectCommand::execute() {
	controller->createObject();
	std::shared_ptr<ICommand> cmd = std::make_shared<CreateObjectCommand>(controller);
	controller->addToHistory(cmd);
}