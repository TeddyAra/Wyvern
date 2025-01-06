#pragma once

#include <memory>
#include <vector>

#include "ICommand.h"
#include "Camera.h"
#include "TransformTools.h"

class World;
class HistoryManager;

class InteractionController {
public:
	InteractionController(std::shared_ptr<World> world);
	~InteractionController();

	std::shared_ptr<Camera> getCamera();

	float getDebug();
	void setDebug(float debug);
	void addObject(std::shared_ptr<Transform> object);

	void changeTool(TransformTools::Tool tool);

	std::vector<std::shared_ptr<Transform>>& getObjects();
	std::vector<std::shared_ptr<Transform>>& getTransformTools();

	void addToHistory(std::shared_ptr<ICommand> command);
	
	void undo();
	void redo();

private:
	std::shared_ptr<World> world;
	std::unique_ptr<HistoryManager> history;
};