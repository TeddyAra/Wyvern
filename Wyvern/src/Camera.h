#pragma once

#include "Transform.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Camera : public Transform {
public:
	Camera(float fov);
	~Camera();

	glm::mat4 getViewMatrix();
	glm::mat4 getProjectionMatrix(glm::vec2 viewportSize);

	void setFov(float fov);
	float getFov();

private:
	float fov;
};