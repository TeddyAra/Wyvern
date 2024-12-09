#pragma once

#include <memory>

#include "Camera.h"
#include "CameraController.h"

class World {
public:
	World();
	~World();

	std::shared_ptr<Camera> getCamera();
	void updateCamera();

	float getDebug();
	void setDebug(float debug);

private:
	std::shared_ptr<Camera> camera;
	std::shared_ptr<CameraController> controller;

	float debug;
};