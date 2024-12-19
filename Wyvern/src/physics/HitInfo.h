#pragma once

#include <memory>

#include "glm/glm.hpp"

#include "Transform.h"

class HitInfo {
public:
	HitInfo();
	~HitInfo();

	std::shared_ptr<Transform> object;
	glm::vec3 hitPoint;
	glm::vec3 normal;
	float distance;
};