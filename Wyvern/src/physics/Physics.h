#pragma once

#include "Renderer.h"

#include <memory>
#include <vector>
#include <algorithm>
#include <string>

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

	static bool ray(glm::vec3 origin, glm::vec3 direction, HitInfo& info, int layer = -1, float maxLength = -1.0f);
	static bool rayPlane(glm::vec3 origin, glm::vec3 direction, glm::vec3 planeOrigin, glm::vec3 planeNormal, HitInfo& info, float maxLength = -1.0f);

	static void addLayer(int ID, const std::string& layer);
	static int getLayerIndex(const std::string& layer);

	static std::string vec3ToString(glm::vec3 vec);

private:
	static std::vector<std::shared_ptr<Transform>> objects;
	//static std::map<int, std::string> layers;
	static std::map<std::string, int> layers;
};