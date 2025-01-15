#pragma once

#include "ICommand.h"

class SetRotationSnapCommand : public ICommand {
public:
	explicit SetRotationSnapCommand(std::shared_ptr<InteractionController> controller);
	void execute() override;
};