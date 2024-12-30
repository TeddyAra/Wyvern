#pragma once 

#include "Collider.h"

class CylinderCollider : public Collider {
public:
	CylinderCollider();
	~CylinderCollider();

	std::vector<glm::vec3> getVertices() override;
	std::vector<unsigned int> getIndices() override;
};