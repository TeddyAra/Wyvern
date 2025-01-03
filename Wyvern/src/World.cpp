#include "World.h"

#include <iostream>

#include "CameraBehaviour.h"

World::World(int defaultLayer)
	: debug(0.0f), camera(std::make_shared<Camera>(60)), defaultLayer(defaultLayer), 
	sunDirection(glm::normalize(glm::vec3(0.1f, -1.0f, 0.5f))), sunStrength(0.8f),
	ambientLight(glm::vec3(0.0f, 0.15f, 0.85f)), ambientStrength(0.1f)
{
	camera->setBehaviour(std::make_shared<CameraBehaviour>());

	glm::vec3 directions[] = {
		{  1.0f,  0.0f,  0.0f },
		{ -1.0f,  0.0f,  0.0f },
		{  0.0f,  1.0f,  0.0f },
		{  0.0f, -1.0f,  0.0f },
		{  0.0f,  0.0f,  1.0f },
		{  0.0f,  0.0f, -1.0f }
	};

	for (const glm::vec3& direction : directions) {
		std::shared_ptr<Transform> tool = std::make_shared<Transform>();
		tool->setScale(0.1f, 0.1f, 2.0f);
		tool->lookAt(direction);
		tool->translate(direction * 2.0f);

		tool->removeLayer(Physics::getLayerIndex("main"));
		tool->addLayer(Physics::getLayerIndex("transform"));
		tool->setCollider(std::make_shared<CylinderCollider>());

		transform.push_back(tool);
		Physics::addObject(tool);
	}

	const float baseWidth = 100.0f;
	const float baseHeight = 25.0f;

	std::shared_ptr<Transform> base = std::make_shared<Transform>();
	base->setScale(baseWidth, baseHeight, baseWidth);
	base->setPosition(0.0f, baseHeight * -0.5f, 0.0f);
	addObject(base);
}

World::~World() {
	objects.clear();
	selected.clear();
	transform.clear();
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

std::vector<std::shared_ptr<Transform>>& World::getObjects() {
	return objects;
}

std::vector<std::shared_ptr<Transform>>& World::getSelected() {
	return selected;
}

std::vector<std::shared_ptr<Transform>>& World::getTransformTools() {
	return transform;
}

void World::addObject(std::shared_ptr<Transform> object) {
	object->addLayer(defaultLayer);
	objects.push_back(object);
	Physics::addObject(object);
}

float World::getDebug() {
	return debug;
}

void World::setDebug(float debug) {
	this->debug = debug;
}

void World::checkIntersections() {
	if (Input::getMouseDown(0)) {
		// Ignore mouse click if it isn't in the viewport
		if (!Input::isPosInsideRect(Input::getMousePosition(), viewportPos, viewportSize)) {
			return;
		}

		glm::vec2 mousePos = Input::getMousePosition() - viewportPos;

		glm::vec3 rayOrigin = camera->getPosition();
		glm::vec3 rayDirection = camera->getModelMatrix() * glm::vec4(Input::posToRayDirection(mousePos, viewportSize, camera->getFov()), 0.0f);
		rayDirection = glm::normalize(rayDirection);

		HitInfo info;
		if (Physics::ray(rayOrigin, rayDirection, info, Physics::getLayerIndex("transform"))) {
			std::cout << "Transform" << std::endl;
			return;
		}

		// Clear selection if left control isn't held
		if (!Input::getKey(GLFW_KEY_LEFT_CONTROL)) {
			selected.clear();
		}

		if (Physics::ray(rayOrigin, rayDirection, info, Physics::getLayerIndex("main"))) {
			std::cout << "Main" << std::endl;
			selected.push_back(info.object);
		}
	}
}

glm::vec3 World::getSunDirection() {
	return sunDirection;
}

float World::getSunStrength() {
	return sunStrength;
}

glm::vec3 World::getAmbientLight() {
	return ambientLight;
}

float World::getAmbientStrength() {
	return ambientStrength;
}

void World::setDefaultLayer(int ID) {
	defaultLayer = ID;
}