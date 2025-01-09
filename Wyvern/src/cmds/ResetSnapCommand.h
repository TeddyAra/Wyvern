#pragma once

#include "ICommand.h"

class ResetSnapCommand : public ICommand {
public:
	explicit ResetSnapCommand(std::shared_ptr<InteractionController> controller);
	void execute() override;
};