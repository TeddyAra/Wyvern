#pragma once

#include "Transform.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Camera : public Transform {
public:
	Camera(float fov);
	~Camera();

	glm::mat4 getViewMatrix();

	void setFov(float fov);
	float getFov();

private:
	float fov;
};