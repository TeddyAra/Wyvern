#pragma once

#include <memory>
#include <vector>

#include "ICommand.h"

//#include "World.h"
//#include "HistoryManager.h"

class World;
class HistoryManager;

class InteractionController {
public:
	InteractionController();
	~InteractionController();

	float getDebug();
	void setDebug(float debug);
	void addToHistory(std::shared_ptr<ICommand> command);
	void undo();
	void redo();

private:
	std::unique_ptr<World> world;
	std::unique_ptr<HistoryManager> history;
};