#pragma once

#include <vector>

#include "glm/glm.hpp"

class Collider {
public:
	Collider() {}
	virtual ~Collider() = default;

	virtual std::vector<glm::vec3> getVertices() = 0;

	virtual std::vector<unsigned int> getIndices() = 0;

protected:
	std::vector<glm::vec3> vertices;
	std::vector<unsigned int> indices;
};