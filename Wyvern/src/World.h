#pragma once

#include <memory>
#include <vector>

#include "Camera.h"
#include "Transform.h"

class World {
public:
	World();
	~World();

	std::shared_ptr<Camera> getCamera();
	void start();
	void update();

	void addObject(std::shared_ptr<Transform> object);

	float getDebug();
	void setDebug(float debug);

private:
	std::vector<std::shared_ptr<Transform>> objects;
	std::shared_ptr<Camera> camera;

	float debug;
};