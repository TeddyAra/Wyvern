#pragma once 

#include "Collider.h"

class BoxCollider : public Collider {
public:
	BoxCollider();
	~BoxCollider();

	std::vector<glm::vec3> getVertices() override;
	std::vector<unsigned int> getIndices() override;
};