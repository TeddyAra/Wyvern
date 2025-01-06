#pragma once

#include "ICommand.h"

class ToggleHitboxesCommand : public ICommand {
public:
	explicit ToggleHitboxesCommand(std::shared_ptr<InteractionController> controller);
	void execute() override;
};