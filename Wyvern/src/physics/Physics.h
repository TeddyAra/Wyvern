#pragma once

#include <memory>
#include <vector>
#include <algorithm>

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/intersect.hpp"

#include "HitInfo.h"
#include "Transform.h"

class Physics {
public:
	Physics() = delete;

	static void addObject(std::shared_ptr<Transform> object);
	static void removeObject(std::shared_ptr<Transform> object);

	static bool ray(glm::vec3 origin, glm::vec3 direction, HitInfo& info);

private:
	static std::vector<std::shared_ptr<Transform>> objects;
};