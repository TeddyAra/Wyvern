#pragma once

#include "Camera.h"
#include "Transform.h"

#include <memory>
#include <vector>

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
	Tool getTool();
	void checkTool();
	std::vector<std::shared_ptr<Transform>>& getTransformTools();

private:
	Tool currentTool;
	std::vector<std::shared_ptr<Transform>> transform;
	glm::vec3 originalScale;
	World* world;
	std::shared_ptr<Camera> camera;
	bool transforming;

	glm::vec3 selectionOrigin;
	glm::vec3 selectionSize;

	glm::vec3 originalPos;
	glm::vec3 planeOrigin;
	glm::vec3 planeDirection;

	glm::vec3 directions[6] = {
		{  1.0f,  0.0f,  0.0f },
		{ -1.0f,  0.0f,  0.0f },
		{  0.0f,  1.0f,  0.0f },
		{  0.0f, -1.0f,  0.0f },
		{  0.0f,  0.0f,  1.0f },
		{  0.0f,  0.0f, -1.0f }
	};

	void updateScale();
};