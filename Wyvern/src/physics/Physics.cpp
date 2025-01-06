#include "Physics.h"

#include <iostream>

#include "Debug.h"

std::vector<std::shared_ptr<Transform>> Physics::objects;
std::map<int, std::string> Physics::layers;

void Physics::addObject(std::shared_ptr<Transform> object) {
	objects.push_back(object);
}

void Physics::removeObject(std::shared_ptr<Transform> object) {
	auto position = std::find(objects.begin(), objects.end(), object);
	if (position != objects.end()) { 
		objects.erase(position);
	}
}

bool Physics::ray(glm::vec3 origin, glm::vec3 direction, HitInfo& info, int layer, float maxLength) {
	direction = glm::normalize(direction);
	
	float shortestDistance = std::numeric_limits<float>::max();
	glm::vec2 shortestBaryPosition(0.0f, 0.0f);
	std::shared_ptr<Transform> closestObject = nullptr;

	glm::vec3 closestPos1;
	glm::vec3 closestPos2;
	glm::vec3 closestPos3;

	for (const std::shared_ptr<Transform>& object : objects) {
		if (!object->getCollider() || (!object->checkLayer(layer) && layer >= 0)) continue;

		std::vector<glm::vec3> vertices = object->getCollider()->getVertices();
		std::vector<unsigned int> indices = object->getCollider()->getIndices();
		
		glm::mat4 matrix = object->getModelMatrix();

		for (int i = 0; i < vertices.size(); i++) {
			vertices[i] = glm::vec3(matrix * glm::vec4(vertices[i], 1.0f));
		}

		for (int i = 0; i < indices.size(); i += 3) {
			glm::vec2 triangleBaryPosition;
			float triangleDistance;

			glm::vec3 pos1 = vertices[indices[i]];
			glm::vec3 pos2 = vertices[indices[i + 1]];
			glm::vec3 pos3 = vertices[indices[i + 2]];

			if (glm::intersectRayTriangle(origin, direction, pos1, pos2, pos3, triangleBaryPosition, triangleDistance)) {
				if (triangleDistance < 0 || (triangleDistance > maxLength && maxLength > 0.0f)) continue;

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

bool Physics::rayPlane(glm::vec3 origin, glm::vec3 direction, glm::vec3 planeOrigin, glm::vec3 planeNormal, HitInfo& info, float maxLength) {
	float length = -1.0f;
	if (glm::intersectRayPlane(origin, direction, planeOrigin, planeNormal, length)) {
		if (length < 0 || (maxLength != -1 && length > maxLength)) return false;
		info.distance = length;
		info.hitPoint = origin + direction * length;
		return true;
	}

	return false;
}

void Physics::addLayer(int ID, const std::string& layer) {
	if (ID < 0) {
		std::cerr << "Layer must have a positive ID" << std::endl;
		return;
	}

	if (layers.find(ID) != layers.end()) {
		std::cout << "Layer with ID " << ID << " already exists" << std::endl;
		return;
	}

	layers[ID] = layer;
}

int Physics::getLayerIndex(const std::string& layer) {
	int ID = -1;

	std::map<int, std::string>::iterator it;
	for (it = layers.begin(); it != layers.end(); it++) {
		if (it->second == layer) {
			ID = it->first;
			break;
		}
	}

	if (ID >= 0) {
		return ID;
	} else {
		std::cerr << "Layer " << layer << " does not exist" << std::endl;
		return -1;
	}
}

std::string Physics::vec3ToString(glm::vec3 vec) {
	return std::string("(" + std::to_string(vec.x) + ", " + std::to_string(vec.y) + ", " + std::to_string(vec.z) + ")");
}