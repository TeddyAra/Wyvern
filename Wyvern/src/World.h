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
#include "BoxCollider.h"

class World {
public:
	World();
	~World();

	std::shared_ptr<Camera> getCamera();
	void start();
	void update();

	void updateViewport(float posX, float posY, float viewportWidth, float viewportHeight);

	std::vector<std::shared_ptr<Transform>> getObjects();
	std::vector<std::shared_ptr<Transform>> getSelected();
	void addObject(std::shared_ptr<Transform> object);

	float getDebug();
	void setDebug(float debug);
	void createObject();

private:
	std::vector<std::shared_ptr<Transform>> objects;
	std::vector<std::shared_ptr<Transform>> selected;
	std::shared_ptr<Camera> camera;

	glm::vec2 viewportPos;
	glm::vec2 viewportSize;

	void checkIntersections();

	float debug;
};