#pragma once

#include "ICommand.h"

class ToggleRotationSnapCommand : public ICommand {
public:
	explicit ToggleRotationSnapCommand(std::shared_ptr<InteractionController> controller);
	void execute() override;
};