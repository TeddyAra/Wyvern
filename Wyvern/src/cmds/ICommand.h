#pragma once

#include "glm/glm.hpp"

#include <memory>
#include <vector>
#include <any>
#include <optional>
#include <typeinfo>

#include "Physics.h"
#include "HitInfo.h"

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

	template<typename T>
	std::optional<T> getArg() {
		for (std::any arg : args) {
			if (arg.type() == typeid(T)) {
				return std::any_cast<T>(arg);
			}
		}

		return std::nullopt;
	}

protected:
	std::vector<std::any> args;
	std::shared_ptr<InteractionController> controller;
};