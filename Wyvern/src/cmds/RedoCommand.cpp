#include "RedoCommand.h"

#include <iostream>

#include "InteractionController.h"

RedoCommand::RedoCommand(std::shared_ptr<InteractionController> controller)
	: ICommand(controller)
{

}

void RedoCommand::execute() {
	controller->redo();
}