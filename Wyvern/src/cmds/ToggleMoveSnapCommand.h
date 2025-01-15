#pragma once

#include "ICommand.h"

class ToggleMoveSnapCommand : public ICommand {
public:
	explicit ToggleMoveSnapCommand(std::shared_ptr<InteractionController> controller);
	void execute() override;
};