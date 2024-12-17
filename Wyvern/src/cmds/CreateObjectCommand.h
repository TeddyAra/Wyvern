#pragma once

#include "ICommand.h"

class CreateObjectCommand : public ICommand {
public:
	explicit CreateObjectCommand(std::shared_ptr<InteractionController> controller);
	void execute() override;
};