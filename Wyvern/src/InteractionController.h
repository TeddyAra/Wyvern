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
	InteractionController(std::shared_ptr<World> world);
	~InteractionController();

	float getDebug();
	void setDebug(float debug);
	void createObject();

	void addToHistory(std::shared_ptr<ICommand> command);
	
	void undo();
	void redo();

private:
	std::shared_ptr<World> world;
	std::unique_ptr<HistoryManager> history;
};