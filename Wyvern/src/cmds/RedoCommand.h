#pragma once

#include "ICommand.h"

class RedoCommand : public ICommand {
public:
	explicit RedoCommand(std::shared_ptr<InteractionController> controller);
	void execute() override;
};