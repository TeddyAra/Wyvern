#include "World.h"

#include <iostream>

#include "CameraBehaviour.h"

const glm::vec3 vertices[] = {
	{ -0.5f, -0.5f, -0.5f },
	{  0.5f, -0.5f, -0.5f },
	{ -0.5f,  0.5f, -0.5f },
	{  0.5f,  0.5f, -0.5f },
	{ -0.5f, -0.5f,  0.5f },
	{  0.5f, -0.5f,  0.5f },
	{ -0.5f,  0.5f,  0.5f },
	{  0.5f,  0.5f,  0.5f }
};

const unsigned int indices[] = {
	0, 2, 3,
	0, 3, 1,

	1, 3, 7,
	1, 7, 5,

	5, 7, 6,
	5, 6, 4,

	4, 6, 2,
	4, 2, 0,

	4, 0, 1,
	4, 1, 5,

	2, 6, 7,
	2, 7, 3
};

World::World() 
	: debug(0.0f), camera(std::make_shared<Camera>(60))
{
	camera->setBehaviour(std::make_shared<CameraBehaviour>());
}

World::~World() {

}

std::shared_ptr<Camera> World::getCamera() {
	return camera;
}

void World::start() {
	camera->start();

	for (std::shared_ptr<Transform> object : objects) {
		object->start();
	}
}

void World::update() {
	camera->update();

	checkIntersections();

	for (std::shared_ptr<Transform> object : objects) {
		object->update();
	}
}

void World::updateViewport(float posX, float posY, float viewportWidth, float viewportHeight) {
	viewportPos = glm::vec2(posX, posY);
	viewportSize = glm::vec2(viewportWidth, viewportHeight);
}

std::vector<std::shared_ptr<Transform>> World::getObjects() {
	return objects;
}

std::vector<std::shared_ptr<Transform>> World::getSelected() {
	return selected;
}

void World::addObject(std::shared_ptr<Transform> object) {
	objects.push_back(object);
}

float World::getDebug() {
	return debug;
}

void World::setDebug(float debug) {
	this->debug = debug;
	std::cout << "Debug float changed to " << debug << std::endl;
}

void World::checkIntersections() {
	if (Input::getMouseDown(0)) {
		std::cout << "Click" << std::endl;

		if (!Input::isPosInsideRect(Input::getMousePosition(), viewportPos, viewportSize)) {
			std::cout << "Ignored" << std::endl;
			return;
		}

		if (!Input::getKey(GLFW_KEY_LEFT_CONTROL)) {
			std::cout << "Clear" << std::endl;
			selected.clear();
		}

		glm::vec2 mousePos = Input::getMousePosition() - viewportPos;
		std::cout << "Mouse position: " << mousePos.x << " " << mousePos.y << std::endl;

		glm::vec3 rayOrigin = camera->getPosition();
		glm::vec3 rayDirection = Input::getRelativeDirection(camera->getViewMatrix(), Input::posToRayDirection(mousePos, viewportSize, camera->getFov()));
		rayDirection = glm::normalize(rayDirection) * 1000.0f;

		float shortestDistance = std::numeric_limits<float>::max();
		glm::vec2 shortestBaryPosition;
		std::shared_ptr<Transform> closestObject = NULL;

		for (std::shared_ptr<Transform> object : objects) {
			/*glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), object->getPosition()) * glm::mat4_cast(object->getRotation()) * glm::scale(glm::mat4(1.0f), object->getScale());
			modelMatrix = glm::inverse(modelMatrix);

			glm::vec3 localRayOrigin = glm::vec3(modelMatrix * glm::vec4(rayOrigin, 1.0f));
			glm::vec3 localRayDirection = glm::normalize(glm::vec3(modelMatrix * glm::vec4(rayDirection, 1.0f)));

			glm::vec3 min = glm::vec3(-1.0f, -1.0f, -1.0f);
			glm::vec3 max = glm::vec3( 1.0f,  1.0f,  1.0f);

			float tmin = (min.x - localRayOrigin.x) / localRayDirection.x;
			float tmax = (max.x - localRayOrigin.x) / localRayDirection.x;

			if (tmin > tmax) std::swap(tmin, tmax);

			float tymin = (min.y - localRayOrigin.y) / localRayDirection.y;
			float tymax = (max.y - localRayOrigin.y) / localRayDirection.y;

			if (tymin > tymax) std::swap(tymin, tymax);

			if ((tmin > tymax) || (tymin > tmax)) continue;

			if (tymin > tmin) tmin = tymin;
			if (tymax < tmax) tmax = tymax;

			float tzmin = (min.z - localRayOrigin.z) / localRayDirection.z;
			float tzmax = (max.z - localRayOrigin.z) / localRayDirection.z;

			if (tzmin > tzmax) std::swap(tzmin, tzmax);

			if ((tmin > tzmax) || (tzmin > tmax)) continue;

			if (tzmin > tmin) tmin = tzmin;
			if (tzmax < tmax) tmax = tzmax;

			std::cout << "Selected" << std::endl;

			selected.push_back(object);
			return;*/

			glm::vec2 currentBaryPosition;
			float currentShortest = std::numeric_limits<float>::max();

			glm::mat4 matrix = object->getModelMatrix();

			for (int i = 0; i < sizeof(indices) / sizeof(indices[0]); i += 3) {
				glm::vec2 baryPosition;
				float distance;

				glm::vec3 pos1 = glm::vec3(matrix * glm::vec4(vertices[indices[i]],	    1.0f));
				glm::vec3 pos2 = glm::vec3(matrix * glm::vec4(vertices[indices[i + 1]], 1.0f));
				glm::vec3 pos3 = glm::vec3(matrix * glm::vec4(vertices[indices[i + 2]], 1.0f));

				if (glm::intersectRayTriangle(rayOrigin, rayDirection, pos1, pos2, pos3, baryPosition, distance)) {
					if (distance < currentShortest) {
						currentBaryPosition = baryPosition;
						currentShortest = distance;
						std::cout << "Intersect" << std::endl;
					}
				}
			}

			if (currentShortest < shortestDistance) {
				shortestDistance = currentShortest;
				shortestBaryPosition = currentBaryPosition;
				closestObject = object;
			}
		}

		if (closestObject) selected.push_back(closestObject);
	}
}