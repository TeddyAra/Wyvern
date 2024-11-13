#pragma once

#include "ICommand.h"

class DebugCommand : public ICommand {
public:
	explicit DebugCommand(std::shared_ptr<InteractionController> controller);
	void execute() override;
};