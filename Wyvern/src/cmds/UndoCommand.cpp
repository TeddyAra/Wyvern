#include "UndoCommand.h"

#include <iostream>

#include "InteractionController.h"

UndoCommand::UndoCommand(std::shared_ptr<InteractionController> controller)
	: ICommand(controller) 
{

}

void UndoCommand::execute() {
	controller->undo();
}