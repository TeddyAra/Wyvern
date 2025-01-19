#include "ApplyColourCommand.h"

#include "InteractionController.h"

ApplyColourCommand::ApplyColourCommand(std::shared_ptr<InteractionController> controller)
	: ICommand(controller) 
{

}

void ApplyColourCommand::execute() {
	controller->applyColour();
}