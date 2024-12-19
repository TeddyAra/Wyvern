#include "Physics.h"

#include <iostream>

std::vector<std::shared_ptr<Transform>> Physics::objects;

void Physics::addObject(std::shared_ptr<Transform> object) {
	objects.push_back(object);
	std::cout << "Added: " << objects.size() << std::endl;
}

void Physics::removeObject(std::shared_ptr<Transform> object) {
	auto position = std::find(objects.begin(), objects.end(), object);
	if (position != objects.end()) { 
		objects.erase(position);
	}
}

bool Physics::ray(glm::vec3 origin, glm::vec3 direction, HitInfo& info) {
	const float distance = 1; //1000.0f;
	direction = glm::normalize(direction) * distance;
	
	float shortestDistance = std::numeric_limits<float>::max();
	glm::vec2 shortestBaryPosition;
	std::shared_ptr<Transform> closestObject = nullptr;

	glm::vec3 closestPos1;
	glm::vec3 closestPos2;
	glm::vec3 closestPos3;
	
	std::cout << objects.size() << std::endl;

	for (std::shared_ptr<Transform> object : objects) {
		std::cout << "Object" << std::endl;

		if (!object->getCollider()) continue;

		std::vector<glm::vec3> vertices = object->getCollider()->getVertices();
		std::vector<unsigned int> indices = object->getCollider()->getIndices();
		
		glm::mat4 matrix = object->getModelMatrix();

		for (int i = 0; i < indices.size(); i += 3) {
			glm::vec2 triangleBaryPosition;
			float triangleDistance;

			glm::vec3 pos1 = glm::vec3(matrix * glm::vec4(vertices[indices[i]], 1.0f));
			glm::vec3 pos2 = glm::vec3(matrix * glm::vec4(vertices[indices[i + 1]], 1.0f));
			glm::vec3 pos3 = glm::vec3(matrix * glm::vec4(vertices[indices[i + 2]], 1.0f));

			if (glm::intersectRayTriangle(origin, direction, pos1, pos2, pos3, triangleBaryPosition, triangleDistance)) {
				if (triangleDistance < shortestDistance) {
					shortestDistance = triangleDistance;
					shortestBaryPosition = triangleBaryPosition;
					closestObject = object;

					closestPos1 = pos1;
					closestPos2 = pos2;
					closestPos3 = pos3;
				}
			}
		}
	}

	if (!closestObject) return false;

	glm::vec3 hitPoint = (1.0f - shortestBaryPosition.x - shortestBaryPosition.y) * closestPos1 +
		shortestBaryPosition.x * closestPos2 +
		shortestBaryPosition.y * closestPos3;

	glm::vec3 edge1 = closestPos2 - closestPos1;
	glm::vec3 edge2 = closestPos3 - closestPos1;
	glm::vec3 normal = glm::normalize(glm::cross(edge1, edge2));

	info.distance = shortestDistance;
	info.hitPoint = hitPoint;
	info.normal = normal;
	info.object = closestObject;
	return true;
}