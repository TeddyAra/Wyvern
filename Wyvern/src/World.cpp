#include "World.h"

#include <iostream>

#include "CameraBehaviour.h"

World* World::worldInstance;

World::World(int defaultLayer)
	: debug(0.0f), camera(std::make_shared<Camera>(60)), defaultLayer(defaultLayer),
	sunDirection(glm::normalize(glm::vec3(0.1f, -1.0f, 0.5f))), sunStrength(0.8f),
	ambientLight(glm::vec3(0.0f, 0.15f, 0.85f)), ambientStrength(0.1f)
{
	if (worldInstance) { 
		std::cerr << "World already exists" << std::endl;
		return;
	}
	
	worldInstance = this;

	camera->setBehaviour(std::make_shared<CameraBehaviour>());
	transformTools = std::make_unique<TransformTools>();

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

		tool->removeLayer(Physics::getLayerIndex("main"));
		tool->addLayer(Physics::getLayerIndex("transform"));
		tool->addLayer(Physics::getLayerIndex("move"));
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

World* World::getWorld() {
	return worldInstance;
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

	transformTools->checkTool();

	for (std::shared_ptr<Transform> object : objects) {
		object->update();
	}
}

void World::changeTool(TransformTools::Tool tool) {
	transformTools->changeTool(tool);
}

void World::updateViewport(float posX, float posY, float viewportWidth, float viewportHeight) {
	viewportPos = glm::vec2(posX, posY);
	viewportSize = glm::vec2(viewportWidth, viewportHeight);
}

glm::vec2 World::getViewportPos() {
	return viewportPos;
}

glm::vec2 World::getViewportSize() {
	return viewportSize;
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