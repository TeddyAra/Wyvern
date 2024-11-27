#pragma once

#include "ICommand.h"

class UndoCommand : public ICommand {
public:
	explicit UndoCommand(std::shared_ptr<InteractionController> controller);
	void execute() override;
};