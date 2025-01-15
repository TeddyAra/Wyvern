#pragma once

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/intersect.hpp"

#include <memory>
#include <vector>

#include "Camera.h"
#include "Transform.h"
#include "Physics.h"
#include "TransformTools.h"

#include "BoxCollider.h"
#include "CylinderCollider.h"

class World {
public:
	World(int defaultLayer);
	~World();

	static World* getWorld();

	std::shared_ptr<Camera> getCamera();
	void start();
	void update();

	void updateViewport(float posX, float posY, float viewportWidth, float viewportHeight);
	glm::vec2 getViewportPos();
	glm::vec2 getViewportSize();

	void changeTool(TransformTools::Tool tool);
	TransformTools::Tool getTool();

	std::vector<std::shared_ptr<Transform>>& getObjects();
	std::vector<std::shared_ptr<Transform>>& getSelected();
	std::vector<std::shared_ptr<Transform>>& getTransformTools();
	void addObject(std::shared_ptr<Transform> object);

	void toggleMoveSnap(bool value);
	void toggleRotationSnap(bool value);
	void setMoveSnap(float snap);
	void setRotationSnap(float snap);
	float getMoveSnap();
	float getRotationSnap();

	glm::vec3 getSunDirection();
	float getSunStrength();
	glm::vec3 getAmbientLight();
	float getAmbientStrength();

	void setDefaultLayer(int ID);

private:
	std::vector<std::shared_ptr<Transform>> objects;
	std::vector<std::shared_ptr<Transform>> selected;
	std::shared_ptr<Camera> camera;
	std::unique_ptr<TransformTools> transformTools;

	glm::vec2 viewportPos;
	glm::vec2 viewportSize;

	glm::vec3 sunDirection;
	float sunStrength;
	glm::vec3 ambientLight;
	float ambientStrength;

	int defaultLayer;

	static World* worldInstance;
	void createObject(glm::vec3 pos, glm::vec3 rot, glm::vec3 size, glm::vec3 col);
	void createWorld();
};