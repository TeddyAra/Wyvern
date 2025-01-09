#include "CommandTemplate.h"

#include "InteractionController.h"

CommandTemplate::CommandTemplate(std::shared_ptr<InteractionController> controller) 
	: ICommand(controller) 
{ 

}

void CommandTemplate::execute() {

}