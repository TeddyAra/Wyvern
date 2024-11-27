#pragma once

#include <memory>
#include <vector>
#include <any>

class InteractionController;

class ICommand {
public:
	explicit ICommand(std::shared_ptr<InteractionController> controller)
		: controller(controller) {}
	virtual void execute() = 0;
	virtual ~ICommand() = default;
	void setArgs(std::vector<std::any> args) {
		this->args = args;
	}

protected:
	std::vector<std::any> args;
	std::shared_ptr<InteractionController> controller;
};