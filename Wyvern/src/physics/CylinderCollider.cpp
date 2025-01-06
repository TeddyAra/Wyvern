#include "CylinderCollider.h"

#include <iostream>

#include "glm/gtc/matrix_transform.hpp"

CylinderCollider::CylinderCollider()
	: Collider() 
{
	const int faceCount = 16;

	glm::vec3 axis(0.0f, 0.0f, 1.0f);

	vertices.push_back(axis * 0.5f);
	vertices.push_back(axis * -0.5f);

	for (float i = 0; i < 360; i += 360 / faceCount) {
		glm::vec3 vertex(0.0f, 0.5f, 0.0f);
		glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(i), axis);
		vertex = glm::vec3(rotationMatrix * glm::vec4(vertex, 0.0f));

		vertices.push_back(vertex - glm::vec3(0.0f, 0.0f, 0.5f));
		vertices.push_back(vertex + glm::vec3(0.0f, 0.0f, 0.5f));
	}

	if (vertices.size() < 8) {
		std::cerr << "Cylinder colliders do not have enough faces" << std::endl;
		return;
	}

	for (int i = 4; i < vertices.size(); i += 2) {
		// Bottom
		indices.push_back(i - 2);
		indices.push_back(i    );
		indices.push_back(0    );

		// Top
		indices.push_back(i - 1);
		indices.push_back(1    );
		indices.push_back(i + 1);

		// Side
		indices.push_back(i - 2);
		indices.push_back(i - 1);
		indices.push_back(i + 1);

		indices.push_back(i - 2);
		indices.push_back(i + 1);
		indices.push_back(i    );
	}
}

CylinderCollider::~CylinderCollider() {

}

std::vector<glm::vec3> CylinderCollider::getVertices() {
	return vertices;
}

std::vector<unsigned int> CylinderCollider::getIndices() {
	return indices;
}