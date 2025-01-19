#pragma once

#include "ICommand.h"

class SetColourCommand : public ICommand {
public:
	explicit SetColourCommand(std::shared_ptr<InteractionController> controller, int index);
	void execute() override;

private:
	int index;
};