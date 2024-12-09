#pragma once

#include <memory>

#include "Camera.h"
#include "Input.h"

class CameraController {
public:
	CameraController(std::shared_ptr<Camera> camera);
	~CameraController();

	void update(float deltaTime);

private:
	std::shared_ptr<Camera> camera;

	const float slowSpeed = 1.0f;
	const float fastSpeed = 2.0f;
	const float sensitivity = 0.25f;
};