#pragma once

#include <memory>

#include "InteractionController.h"

class ICommand {
public:
	explicit ICommand(std::shared_ptr<InteractionController> controller)
		: controller(controller) {}
	virtual void execute() = 0;
	virtual ~ICommand() = default;

protected:
	std::shared_ptr<InteractionController> controller;
};