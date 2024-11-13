#pragma once

#include <memory>

#include "World.h"

class InteractionController {
public:
	InteractionController();
	~InteractionController();

	int getSelected();

private:
	std::unique_ptr<World> world;
};