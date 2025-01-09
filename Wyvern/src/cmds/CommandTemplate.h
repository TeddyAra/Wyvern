#pragma once

#include "ICommand.h"

class CommandTemplate : public ICommand {
public:
	explicit CommandTemplate(std::shared_ptr<InteractionController> controller);
	void execute() override;
};