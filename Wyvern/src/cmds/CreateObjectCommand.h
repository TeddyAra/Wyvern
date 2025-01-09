#pragma once

#include "ICommand.h"

class CreateObjectCommand : public ICommand {
public:
	explicit CreateObjectCommand(std::shared_ptr<InteractionController> controller);
	void execute() override;

private:
	float maxRayLength = 50.0f;
	float standardLength = 10.0f;
};