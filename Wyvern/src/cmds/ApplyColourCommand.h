#pragma once

#include "ICommand.h"

class ApplyColourCommand : public ICommand {
public:
	explicit ApplyColourCommand(std::shared_ptr<InteractionController> controller);
	void execute() override;
};