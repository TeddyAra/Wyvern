#pragma once

#include "ICommand.h"

class SetMoveSnapCommand : public ICommand {
public:
	explicit SetMoveSnapCommand(std::shared_ptr<InteractionController> controller);
	void execute() override;
};