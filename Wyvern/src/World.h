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
#include "CylinderCollider.h"

class World {
public:
	World(int defaultLayer);
	~World();

	std::shared_ptr<Camera> getCamera();
	void start();
	void update();

	void updateViewport(float posX, float posY, float viewportWidth, float viewportHeight);

	std::vector<std::shared_ptr<Transform>>& getObjects();
	std::vector<std::shared_ptr<Transform>>& getSelected();
	std::vector<std::shared_ptr<Transform>>& getTransformTools();
	void addObject(std::shared_ptr<Transform> object);

	float getDebug();
	void setDebug(float debug);

	glm::vec3 getSunDirection();
	float getSunStrength();
	glm::vec3 getAmbientLight();
	float getAmbientStrength();

	void setDefaultLayer(int ID);

private:
	std::vector<std::shared_ptr<Transform>> objects;
	std::vector<std::shared_ptr<Transform>> selected;
	std::vector<std::shared_ptr<Transform>> transform;
	std::shared_ptr<Camera> camera;

	glm::vec2 viewportPos;
	glm::vec2 viewportSize;

	void checkIntersections();

	glm::vec3 sunDirection;
	float sunStrength;
	glm::vec3 ambientLight;
	float ambientStrength;

	int defaultLayer;
	float debug;
};