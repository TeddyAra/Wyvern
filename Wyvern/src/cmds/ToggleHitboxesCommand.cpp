#include "ToggleHitboxesCommand.h"

#include <iostream>

#include "InteractionController.h"

#include "Debug.h"

ToggleHitboxesCommand::ToggleHitboxesCommand(std::shared_ptr<InteractionController> controller)
	: ICommand(controller)
{

}

void ToggleHitboxesCommand::execute() {
	if (auto arg = getArg<bool>()) {
		Debug::setDrawHitboxes(*arg);
	}
}