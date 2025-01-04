#pragma once

#include "Camera.h"

class World;

class TransformTools {
public:
	TransformTools();
	~TransformTools();

	enum Tool {
		Select = 0,
		Move = 1,
		Scale = 2,
		Rotate = 3
	};

	void changeTool(Tool tool);
	void checkTool();

private:
	Tool currentTool;
	World* world;
	std::shared_ptr<Camera> camera;
	bool transforming;
};