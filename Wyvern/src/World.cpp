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
	Physics::addObject(object);
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
		rayDirection = glm::normalize(rayDirection);

		// TODO: Either shortestDistance or the intersection itself isn't entirely accurate
		HitInfo info;
		if (Physics::ray(rayOrigin, rayDirection, info)) {
			selected.push_back(info.object);
		}
	}
}

void World::createObject() {
	std::shared_ptr<Transform> object = std::make_shared<Transform>();
	object->translate(debug, 0.0f, 0.0f);
	object->setCollider(std::make_shared<BoxCollider>());
	objects.push_back(object);
	Physics::addObject(object);
}