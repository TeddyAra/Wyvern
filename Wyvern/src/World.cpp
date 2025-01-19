#include "World.h"

#include <iostream>

#include "CameraBehaviour.h"
#include "Debug.h"

World* World::worldInstance;

World::World(int defaultLayer)
	: camera(std::make_shared<Camera>(60)), defaultLayer(defaultLayer),
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

	const float baseWidth = 100.0f;
	const float baseHeight = 25.0f;

	std::shared_ptr<Transform> base = std::make_shared<Transform>();
	base->setScale(baseWidth, baseHeight, baseWidth);
	base->setPosition(0.0f, baseHeight * -0.5f, 0.0f);
	base->setGrid(true);
	addObject(base);
	base->setColour(0.9f, 0.9f, 0.9f);

	createWorld();
}

World::~World() {
	objects.clear();
	selected.clear();
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

TransformTools::Tool World::getTool() {
	return transformTools->getTool();
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

void World::applyColour() {
	for (std::shared_ptr<Transform> object : selected) {
		object->setColour(colour);
	}
}

void World::setColour(float colour, int index) {
	this->colour[index] = colour;
}

std::vector<std::shared_ptr<Transform>>& World::getObjects() {
	return objects;
}

std::vector<std::shared_ptr<Transform>>& World::getSelected() {
	return selected;
}

std::vector<std::shared_ptr<Transform>>& World::getTransformTools() {
	return transformTools->getTransformTools();
}

void World::addObject(std::shared_ptr<Transform> object) {
	object->addLayer(defaultLayer);
	object->setColour(colour);
	objects.push_back(object);
	Physics::addObject(object);
	Debug::addObject(object);
	object->start();
}

void World::toggleMoveSnap(bool value) {
	transformTools->toggleMoveSnap(value);
}

void World::toggleRotationSnap(bool value) {
	transformTools->toggleRotationSnap(value);
}

void World::setMoveSnap(float snap) {
	transformTools->setMoveSnap(snap);
}

void World::setRotationSnap(float snap) {
	transformTools->setRotationSnap(snap);
}

float World::getMoveSnap() {
	return transformTools->getMoveSnap();
}

float World::getRotationSnap() {
	return transformTools->getRotationSnap();
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

void World::createObject(glm::vec3 pos, glm::vec3 rot, glm::vec3 size, glm::vec3 col) {
	std::shared_ptr<Transform> object = std::make_shared<Transform>();
	pos.z *= -1;
	rot.x *= -1;

	pos *= 0.5f;
	size *= 0.5f;

	object->setPosition(pos);
	object->setRotation(rot);
	object->setScale(size);
	addObject(object);
	object->setColour(col);
}

void World::createWorld() {    
	createObject(glm::vec3(-1.000, 82.000, 22.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(9.000, 8.000, 2.000), glm::vec3(0.388, 0.373, 0.384));
	createObject(glm::vec3(-1.000, 87.500, 22.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(6.000, 1.000, 4.000), glm::vec3(0.388, 0.373, 0.384));
	createObject(glm::vec3(-1.000, 83.250, 26.250), glm::vec3(0.000, 0.000, 0.000), glm::vec3(5.000, 0.500, 2.500), glm::vec3(0.388, 0.373, 0.384));
	createObject(glm::vec3(-1.000, 82.500, 22.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(8.000, 9.000, 6.000), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(-1.000, 88.500, 22.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(8.000, 1.000, 6.000), glm::vec3(0.388, 0.373, 0.384));
	createObject(glm::vec3(-1.000, 78.812, 23.436), glm::vec3(15.000, 0.000, 0.000), glm::vec3(18.000, 1.000, 20.000), glm::vec3(0.388, 0.373, 0.384));
	createObject(glm::vec3(-1.000, 75.785, 23.142), glm::vec3(15.000, 0.000, 0.000), glm::vec3(14.000, 5.000, 17.000), glm::vec3(0.431, 0.600, 0.792));
	createObject(glm::vec3(-6.635, 84.974, 10.000), glm::vec3(0.000, 0.000, 30.000), glm::vec3(22.000, 0.250, 1.000), glm::vec3(0.388, 0.373, 0.384));
	createObject(glm::vec3(-6.635, 84.974, 12.000), glm::vec3(0.000, 0.000, 30.000), glm::vec3(22.000, 0.250, 1.000), glm::vec3(0.388, 0.373, 0.384));
	createObject(glm::vec3(-6.635, 84.974, 14.000), glm::vec3(0.000, 0.000, 30.000), glm::vec3(22.000, 0.250, 1.000), glm::vec3(0.388, 0.373, 0.384));
	createObject(glm::vec3(-6.635, 84.974, 16.000), glm::vec3(0.000, 0.000, 30.000), glm::vec3(22.000, 0.250, 1.000), glm::vec3(0.388, 0.373, 0.384));
	createObject(glm::vec3(12.634, 84.974, 10.000), glm::vec3(0.000, 0.000, -30.000), glm::vec3(22.000, 0.250, 1.000), glm::vec3(0.388, 0.373, 0.384));
	createObject(glm::vec3(12.634, 84.974, 12.000), glm::vec3(0.000, 0.000, -30.000), glm::vec3(22.000, 0.250, 1.000), glm::vec3(0.388, 0.373, 0.384));
	createObject(glm::vec3(12.634, 84.974, 14.000), glm::vec3(0.000, 0.000, -30.000), glm::vec3(22.000, 0.250, 1.000), glm::vec3(0.388, 0.373, 0.384));
	createObject(glm::vec3(12.634, 84.974, 16.000), glm::vec3(0.000, 0.000, -30.000), glm::vec3(22.000, 0.250, 1.000), glm::vec3(0.388, 0.373, 0.384));
	createObject(glm::vec3(-1.000, 80.500, 26.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(4.000, 5.000, 2.000), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(-1.000, 53.000, 2.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(38.000, 2.000, 26.000), glm::vec3(0.388, 0.373, 0.384));
	createObject(glm::vec3(3.000, 68.000, 2.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(32.000, 24.000, 4.000), glm::vec3(0.549, 0.357, 0.624));
	createObject(glm::vec3(-1.000, 62.000, 23.500), glm::vec3(0.000, 0.000, 0.000), glm::vec3(16.000, 28.000, 17.000), glm::vec3(0.431, 0.600, 0.792));
	createObject(glm::vec3(3.000, 78.000, -4.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(32.000, 4.000, 8.000), glm::vec3(0.549, 0.357, 0.624));
	createObject(glm::vec3(3.000, 78.000, 8.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(32.000, 4.000, 8.000), glm::vec3(0.549, 0.357, 0.624));
	createObject(glm::vec3(-1.000, 50.000, -4.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(40.000, 4.000, 8.000), glm::vec3(0.631, 0.769, 0.549));
	createObject(glm::vec3(-1.000, 48.000, 8.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(40.000, 8.000, 8.000), glm::vec3(0.631, 0.769, 0.549));
	createObject(glm::vec3(-11.250, 72.000, 8.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(0.500, 0.500, 8.000), glm::vec3(0.424, 0.345, 0.294));
	createObject(glm::vec3(-6.072, 84.000, 2.000), glm::vec3(0.000, 0.000, 30.000), glm::vec3(22.000, 2.000, 30.000), glm::vec3(0.388, 0.373, 0.384));
	createObject(glm::vec3(12.071, 84.000, 2.000), glm::vec3(0.000, 0.000, -30.000), glm::vec3(22.000, 2.000, 30.000), glm::vec3(0.388, 0.373, 0.384));
	createObject(glm::vec3(3.000, 89.250, 2.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(1.000, 3.500, 31.000), glm::vec3(0.388, 0.373, 0.384));
	createObject(glm::vec3(9.297, 80.694, 2.000), glm::vec3(0.000, 0.000, -30.000), glm::vec3(14.500, 6.500, 27.000), glm::vec3(0.549, 0.357, 0.624));
	createObject(glm::vec3(3.000, 84.000, 2.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(4.000, 8.000, 28.000), glm::vec3(0.388, 0.373, 0.384));
	createObject(glm::vec3(-3.298, 80.694, 2.000), glm::vec3(0.000, 0.000, 30.000), glm::vec3(14.500, 6.500, 25.000), glm::vec3(0.549, 0.357, 0.624));
	createObject(glm::vec3(-1.000, 55.000, 2.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(42.000, 2.000, 30.000), glm::vec3(0.424, 0.345, 0.294));
	createObject(glm::vec3(-20.750, 53.000, -8.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(1.500, 2.000, 1.000), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(-20.750, 53.000, -6.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(1.500, 2.000, 1.000), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(-20.750, 53.000, -2.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(1.500, 2.000, 1.000), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(-20.750, 53.000, -4.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(1.500, 2.000, 1.000), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(-20.750, 53.000, -0.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(1.500, 2.000, 1.000), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(-20.750, 53.000, 2.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(1.500, 2.000, 1.000), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(-20.750, 53.000, 4.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(1.500, 2.000, 1.000), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(-20.750, 53.000, 6.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(1.500, 2.000, 1.000), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(-20.750, 53.000, 8.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(1.500, 2.000, 1.000), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(-20.750, 53.000, 10.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(1.500, 2.000, 1.000), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(-20.750, 53.000, 12.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(1.500, 2.000, 1.000), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(-20.750, 53.000, 14.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(1.500, 2.000, 1.000), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(18.750, 53.000, 14.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(1.500, 2.000, 1.000), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(18.750, 53.000, 12.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(1.500, 2.000, 1.000), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(18.750, 53.000, 10.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(1.500, 2.000, 1.000), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(18.750, 53.000, 8.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(1.500, 2.000, 1.000), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(18.750, 53.000, 6.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(1.500, 2.000, 1.000), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(18.750, 53.000, 2.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(1.500, 2.000, 1.000), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(18.750, 53.000, -0.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(1.500, 2.000, 1.000), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(18.750, 53.000, -2.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(1.500, 2.000, 1.000), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(18.750, 53.000, -4.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(1.500, 2.000, 1.000), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(18.750, 53.000, -6.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(1.500, 2.000, 1.000), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(18.750, 53.000, -8.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(1.500, 2.000, 1.000), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(18.750, 53.000, -10.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(1.500, 2.000, 1.000), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(18.750, 53.000, 4.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(1.500, 2.000, 1.000), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(-19.000, 53.000, 15.750), glm::vec3(0.000, 0.000, 0.000), glm::vec3(1.000, 2.000, 1.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(-17.000, 53.000, 15.750), glm::vec3(0.000, 0.000, 0.000), glm::vec3(1.000, 2.000, 1.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(-15.000, 53.000, 15.750), glm::vec3(0.000, 0.000, 0.000), glm::vec3(1.000, 2.000, 1.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(-13.000, 53.000, 15.750), glm::vec3(0.000, 0.000, 0.000), glm::vec3(1.000, 2.000, 1.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(-11.000, 53.000, 15.750), glm::vec3(0.000, 0.000, 0.000), glm::vec3(1.000, 2.000, 1.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(-9.000, 53.000, 15.750), glm::vec3(0.000, 0.000, 0.000), glm::vec3(1.000, 2.000, 1.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(3.000, 53.000, -11.750), glm::vec3(0.000, 0.000, 0.000), glm::vec3(1.000, 2.000, 1.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(1.000, 53.000, -11.750), glm::vec3(0.000, 0.000, 0.000), glm::vec3(1.000, 2.000, 1.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(-1.000, 53.000, -11.750), glm::vec3(0.000, 0.000, 0.000), glm::vec3(1.000, 2.000, 1.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(15.000, 53.000, -11.750), glm::vec3(0.000, 0.000, 0.000), glm::vec3(1.000, 2.000, 1.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(13.000, 53.000, -11.750), glm::vec3(0.000, 0.000, 0.000), glm::vec3(1.000, 2.000, 1.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(11.000, 53.000, -11.750), glm::vec3(0.000, 0.000, 0.000), glm::vec3(1.000, 2.000, 1.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(9.000, 53.000, -11.750), glm::vec3(0.000, 0.000, 0.000), glm::vec3(1.000, 2.000, 1.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(7.000, 53.000, -11.750), glm::vec3(0.000, 0.000, 0.000), glm::vec3(1.000, 2.000, 1.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(5.000, 53.000, -11.750), glm::vec3(0.000, 0.000, 0.000), glm::vec3(1.000, 2.000, 1.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(17.000, 53.000, -11.750), glm::vec3(0.000, 0.000, 0.000), glm::vec3(1.000, 2.000, 1.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(-6.635, 84.974, -8.000), glm::vec3(0.000, 0.000, 30.000), glm::vec3(22.000, 0.250, 1.000), glm::vec3(0.388, 0.373, 0.384));
	createObject(glm::vec3(-6.635, 84.974, -6.000), glm::vec3(0.000, 0.000, 30.000), glm::vec3(22.000, 0.250, 1.000), glm::vec3(0.388, 0.373, 0.384));
	createObject(glm::vec3(-6.635, 84.974, -4.000), glm::vec3(0.000, 0.000, 30.000), glm::vec3(22.000, 0.250, 1.000), glm::vec3(0.388, 0.373, 0.384));
	createObject(glm::vec3(-6.635, 84.974, -2.000), glm::vec3(0.000, 0.000, 30.000), glm::vec3(22.000, 0.250, 1.000), glm::vec3(0.388, 0.373, 0.384));
	createObject(glm::vec3(-6.635, 84.974, -0.000), glm::vec3(0.000, 0.000, 30.000), glm::vec3(22.000, 0.250, 1.000), glm::vec3(0.388, 0.373, 0.384));
	createObject(glm::vec3(-6.635, 84.974, 2.000), glm::vec3(0.000, 0.000, 30.000), glm::vec3(22.000, 0.250, 1.000), glm::vec3(0.388, 0.373, 0.384));
	createObject(glm::vec3(-6.635, 84.974, 4.000), glm::vec3(0.000, 0.000, 30.000), glm::vec3(22.000, 0.250, 1.000), glm::vec3(0.388, 0.373, 0.384));
	createObject(glm::vec3(-6.635, 84.974, 6.000), glm::vec3(0.000, 0.000, 30.000), glm::vec3(22.000, 0.250, 1.000), glm::vec3(0.388, 0.373, 0.384));
	createObject(glm::vec3(-6.635, 84.974, 8.000), glm::vec3(0.000, 0.000, 30.000), glm::vec3(22.000, 0.250, 1.000), glm::vec3(0.388, 0.373, 0.384));
	createObject(glm::vec3(12.634, 84.974, -12.000), glm::vec3(0.000, 0.000, -30.000), glm::vec3(22.000, 0.250, 1.000), glm::vec3(0.388, 0.373, 0.384));
	createObject(glm::vec3(12.634, 84.974, -10.000), glm::vec3(0.000, 0.000, -30.000), glm::vec3(22.000, 0.250, 1.000), glm::vec3(0.388, 0.373, 0.384));
	createObject(glm::vec3(12.634, 84.974, -8.000), glm::vec3(0.000, 0.000, -30.000), glm::vec3(22.000, 0.250, 1.000), glm::vec3(0.388, 0.373, 0.384));
	createObject(glm::vec3(12.634, 84.974, -6.000), glm::vec3(0.000, 0.000, -30.000), glm::vec3(22.000, 0.250, 1.000), glm::vec3(0.388, 0.373, 0.384));
	createObject(glm::vec3(12.634, 84.974, -4.000), glm::vec3(0.000, 0.000, -30.000), glm::vec3(22.000, 0.250, 1.000), glm::vec3(0.388, 0.373, 0.384));
	createObject(glm::vec3(12.634, 84.974, -2.000), glm::vec3(0.000, 0.000, -30.000), glm::vec3(22.000, 0.250, 1.000), glm::vec3(0.388, 0.373, 0.384));
	createObject(glm::vec3(12.634, 84.974, -0.000), glm::vec3(0.000, 0.000, -30.000), glm::vec3(22.000, 0.250, 1.000), glm::vec3(0.388, 0.373, 0.384));
	createObject(glm::vec3(12.634, 84.974, 2.000), glm::vec3(0.000, 0.000, -30.000), glm::vec3(22.000, 0.250, 1.000), glm::vec3(0.388, 0.373, 0.384));
	createObject(glm::vec3(12.634, 84.974, 4.000), glm::vec3(0.000, 0.000, -30.000), glm::vec3(22.000, 0.250, 1.000), glm::vec3(0.388, 0.373, 0.384));
	createObject(glm::vec3(12.634, 84.974, 6.000), glm::vec3(0.000, 0.000, -30.000), glm::vec3(22.000, 0.250, 1.000), glm::vec3(0.388, 0.373, 0.384));
	createObject(glm::vec3(12.634, 84.974, 8.000), glm::vec3(0.000, 0.000, -30.000), glm::vec3(22.000, 0.250, 1.000), glm::vec3(0.388, 0.373, 0.384));
	createObject(glm::vec3(-10.500, 63.000, 21.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(3.000, 6.000, 4.000), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(3.000, 60.000, 8.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(32.000, 8.000, 8.000), glm::vec3(0.549, 0.357, 0.624));
	createObject(glm::vec3(-21.000, 57.500, 8.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(1.000, 3.000, 1.000), glm::vec3(0.388, 0.373, 0.384));
	createObject(glm::vec3(4.500, 70.000, -4.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(29.000, 12.000, 8.000), glm::vec3(0.549, 0.357, 0.624));
	createObject(glm::vec3(-10.375, 59.500, 21.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(2.750, 1.000, 3.500), glm::vec3(0.804, 0.804, 0.804));
	createObject(glm::vec3(4.500, 70.000, 8.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(29.000, 12.000, 8.000), glm::vec3(0.549, 0.357, 0.624));
	createObject(glm::vec3(-11.750, 68.000, 8.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(1.500, 0.500, 8.000), glm::vec3(0.424, 0.345, 0.294));
	createObject(glm::vec3(-21.000, 57.500, 16.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(1.000, 3.000, 1.000), glm::vec3(0.388, 0.373, 0.384));
	createObject(glm::vec3(3.000, 68.000, 14.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(32.000, 24.000, 4.000), glm::vec3(0.549, 0.357, 0.624));
	createObject(glm::vec3(-21.000, 57.500, -4.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(1.000, 3.000, 1.000), glm::vec3(0.388, 0.373, 0.384));
	createObject(glm::vec3(-11.125, 64.250, 25.500), glm::vec3(0.000, 0.000, 0.000), glm::vec3(0.250, 3.500, 4.000), glm::vec3(0.804, 0.804, 0.804));
	createObject(glm::vec3(-11.250, 66.000, 8.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(0.500, 4.000, 8.000), glm::vec3(0.686, 0.580, 0.514));
	createObject(glm::vec3(-9.875, 61.500, 24.500), glm::vec3(0.000, 0.000, 0.000), glm::vec3(1.750, 1.000, 6.500), glm::vec3(0.804, 0.804, 0.804));
	createObject(glm::vec3(-11.250, 66.000, -4.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(0.500, 4.000, 8.000), glm::vec3(0.686, 0.580, 0.514));
	createObject(glm::vec3(3.000, 68.000, -10.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(32.000, 24.000, 4.000), glm::vec3(0.549, 0.357, 0.624));
	createObject(glm::vec3(-10.500, 70.000, 8.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(1.000, 12.000, 8.000), glm::vec3(0.067, 0.067, 0.067));
	createObject(glm::vec3(-11.125, 68.875, 24.500), glm::vec3(0.000, 0.000, 0.000), glm::vec3(0.250, 4.750, 6.000), glm::vec3(0.804, 0.804, 0.804));
	createObject(glm::vec3(-13.000, 57.500, 16.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(1.000, 3.000, 1.000), glm::vec3(0.388, 0.373, 0.384));
	createObject(glm::vec3(-12.125, 63.000, 21.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(0.250, 5.000, 3.000), glm::vec3(0.804, 0.804, 0.804));
	createObject(glm::vec3(-11.500, 70.000, -2.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(1.000, 12.000, 0.500), glm::vec3(0.424, 0.345, 0.294));
	createObject(glm::vec3(-21.000, 57.500, 4.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(1.000, 3.000, 1.000), glm::vec3(0.388, 0.373, 0.384));
	createObject(glm::vec3(-11.250, 72.000, -4.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(0.500, 0.500, 8.000), glm::vec3(0.424, 0.345, 0.294));
	createObject(glm::vec3(-21.000, 57.500, -0.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(1.000, 3.000, 1.000), glm::vec3(0.388, 0.373, 0.384));
	createObject(glm::vec3(-10.500, 70.000, -4.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(1.000, 12.000, 8.000), glm::vec3(0.067, 0.067, 0.067));
	createObject(glm::vec3(-21.000, 58.500, 2.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(0.500, 0.500, 27.000), glm::vec3(0.686, 0.580, 0.514));
	createObject(glm::vec3(-11.750, 68.000, -4.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(1.500, 0.500, 8.000), glm::vec3(0.424, 0.345, 0.294));
	createObject(glm::vec3(-21.000, 57.500, 12.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(1.000, 3.000, 1.000), glm::vec3(0.388, 0.373, 0.384));
	createObject(glm::vec3(-17.000, 57.500, 16.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(1.000, 3.000, 1.000), glm::vec3(0.388, 0.373, 0.384));
	createObject(glm::vec3(-11.500, 70.000, 10.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(1.000, 12.000, 0.500), glm::vec3(0.424, 0.345, 0.294));
	createObject(glm::vec3(3.000, 60.000, -4.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(32.000, 8.000, 8.000), glm::vec3(0.549, 0.357, 0.624));
	createObject(glm::vec3(-17.000, 58.500, 16.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(7.000, 0.500, 0.500), glm::vec3(0.686, 0.580, 0.514));
	createObject(glm::vec3(-10.000, 67.000, 24.500), glm::vec3(0.000, 0.000, 0.000), glm::vec3(2.000, 10.000, 7.000), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(-11.500, 70.000, -6.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(1.000, 12.000, 0.500), glm::vec3(0.424, 0.345, 0.294));
	createObject(glm::vec3(-21.000, 57.500, -8.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(1.000, 3.000, 1.000), glm::vec3(0.388, 0.373, 0.384));
	createObject(glm::vec3(-11.500, 70.000, 6.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(1.000, 12.000, 0.500), glm::vec3(0.424, 0.345, 0.294));
	createObject(glm::vec3(-1.000, 42.000, 2.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(40.000, 20.000, 4.000), glm::vec3(0.631, 0.769, 0.549));
	createObject(glm::vec3(-1.000, 42.000, 24.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(16.000, 4.000, 8.000), glm::vec3(0.431, 0.600, 0.792));
	createObject(glm::vec3(-1.000, 46.000, 24.500), glm::vec3(0.000, 0.000, 0.000), glm::vec3(18.000, 4.000, 17.000), glm::vec3(0.431, 0.600, 0.792));
	createObject(glm::vec3(-20.750, 53.000, -10.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(1.500, 2.000, 1.000), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(-9.000, 53.000, -11.750), glm::vec3(0.000, 0.000, 0.000), glm::vec3(1.000, 2.000, 1.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(-11.000, 53.000, -11.750), glm::vec3(0.000, 0.000, 0.000), glm::vec3(1.000, 2.000, 1.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(-13.000, 53.000, -11.750), glm::vec3(0.000, 0.000, 0.000), glm::vec3(1.000, 2.000, 1.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(-15.000, 53.000, -11.750), glm::vec3(0.000, 0.000, 0.000), glm::vec3(1.000, 2.000, 1.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(-17.000, 53.000, -11.750), glm::vec3(0.000, 0.000, 0.000), glm::vec3(1.000, 2.000, 1.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(-19.000, 53.000, -11.750), glm::vec3(0.000, 0.000, 0.000), glm::vec3(1.000, 2.000, 1.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(-3.000, 53.000, -11.750), glm::vec3(0.000, 0.000, 0.000), glm::vec3(1.000, 2.000, 1.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(-5.000, 53.000, -11.750), glm::vec3(0.000, 0.000, 0.000), glm::vec3(1.000, 2.000, 1.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(-7.000, 53.000, -11.750), glm::vec3(0.000, 0.000, 0.000), glm::vec3(1.000, 2.000, 1.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(-6.635, 84.974, -12.000), glm::vec3(0.000, 0.000, 30.000), glm::vec3(22.000, 0.250, 1.000), glm::vec3(0.388, 0.373, 0.384));
	createObject(glm::vec3(-6.635, 84.974, -10.000), glm::vec3(0.000, 0.000, 30.000), glm::vec3(22.000, 0.250, 1.000), glm::vec3(0.388, 0.373, 0.384));
	createObject(glm::vec3(-1.000, 42.000, -10.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(40.000, 20.000, 4.000), glm::vec3(0.631, 0.769, 0.549));
	createObject(glm::vec3(-1.000, 42.000, 14.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(40.000, 20.000, 4.000), glm::vec3(0.631, 0.769, 0.549));
	createObject(glm::vec3(0.500, 42.000, -4.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(37.000, 12.000, 8.000), glm::vec3(0.631, 0.769, 0.549));
	createObject(glm::vec3(0.500, 38.000, 8.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(37.000, 12.000, 8.000), glm::vec3(0.631, 0.769, 0.549));
	createObject(glm::vec3(-19.500, 47.293, -7.293), glm::vec3(-45.000, 0.000, 0.000), glm::vec3(1.000, 2.000, 4.000), glm::vec3(0.686, 0.580, 0.514));
	createObject(glm::vec3(-19.750, 47.750, -4.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(1.500, 0.500, 7.000), glm::vec3(0.424, 0.345, 0.294));
	createObject(glm::vec3(-19.500, 47.293, -0.708), glm::vec3(-45.000, 0.000, 0.000), glm::vec3(1.000, 4.000, 2.000), glm::vec3(0.686, 0.580, 0.514));
	createObject(glm::vec3(-19.750, 43.750, 8.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(1.500, 0.500, 7.000), glm::vec3(0.424, 0.345, 0.294));
	createObject(glm::vec3(-19.500, 43.293, 4.707), glm::vec3(-45.000, 0.000, 0.000), glm::vec3(1.000, 2.000, 4.000), glm::vec3(0.686, 0.580, 0.514));
	createObject(glm::vec3(-19.500, 43.293, 11.292), glm::vec3(-45.000, 0.000, 0.000), glm::vec3(1.000, 4.000, 2.000), glm::vec3(0.686, 0.580, 0.514));
	createObject(glm::vec3(-21.000, 57.500, -12.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(1.000, 3.000, 1.000), glm::vec3(0.388, 0.373, 0.384));
	createObject(glm::vec3(-17.000, 58.500, -12.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(7.000, 0.500, 0.500), glm::vec3(0.686, 0.580, 0.514));
	createObject(glm::vec3(-13.000, 57.500, -12.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(1.000, 3.000, 1.000), glm::vec3(0.388, 0.373, 0.384));
	createObject(glm::vec3(-17.000, 57.500, -12.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(1.000, 3.000, 1.000), glm::vec3(0.388, 0.373, 0.384));
	createObject(glm::vec3(3.000, 80.500, -11.500), glm::vec3(0.000, 0.000, 0.000), glm::vec3(28.500, 1.000, 2.000), glm::vec3(0.388, 0.373, 0.384));
	createObject(glm::vec3(-1.000, 25.750, -22.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(32.000, 3.500, 12.000), glm::vec3(0.745, 0.408, 0.384));
	createObject(glm::vec3(1.000, 25.000, 6.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(36.000, 14.000, 20.000), glm::vec3(0.631, 0.769, 0.549));
	createObject(glm::vec3(-1.000, 40.000, -22.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(32.000, 8.000, 12.000), glm::vec3(0.745, 0.408, 0.384));
	createObject(glm::vec3(-1.000, 36.000, 18.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(16.000, 16.000, 4.000), glm::vec3(0.431, 0.600, 0.792));
	createObject(glm::vec3(-1.000, 21.768, -32.134), glm::vec3(30.000, 0.000, 0.000), glm::vec3(32.000, 4.000, 2.000), glm::vec3(0.424, 0.345, 0.294));
	createObject(glm::vec3(15.134, 21.768, -18.000), glm::vec3(0.000, 0.000, 30.000), glm::vec3(2.000, 4.000, 28.000), glm::vec3(0.424, 0.345, 0.294));
	createObject(glm::vec3(-1.000, 46.812, -23.436), glm::vec3(-15.000, 0.000, 0.000), glm::vec3(36.000, 1.000, 26.000), glm::vec3(0.388, 0.373, 0.384));
	createObject(glm::vec3(-1.000, 43.949, -20.599), glm::vec3(-15.000, 0.000, 0.000), glm::vec3(30.000, 6.000, 22.000), glm::vec3(0.745, 0.408, 0.384));
	createObject(glm::vec3(-1.000, 26.250, 26.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(32.000, 0.500, 20.000), glm::vec3(0.424, 0.345, 0.294));
	createObject(glm::vec3(9.000, 26.189, 32.343), glm::vec3(-15.000, 0.000, 0.000), glm::vec3(4.000, 2.000, 6.000), glm::vec3(0.424, 0.345, 0.294));
	createObject(glm::vec3(9.000, 24.013, 27.088), glm::vec3(-30.000, 0.000, 0.000), glm::vec3(4.000, 2.000, 6.000), glm::vec3(0.424, 0.345, 0.294));
	createObject(glm::vec3(9.000, 20.550, 22.576), glm::vec3(-45.000, 0.000, 0.000), glm::vec3(4.000, 2.000, 6.000), glm::vec3(0.424, 0.345, 0.294));
	createObject(glm::vec3(9.000, 16.038, 19.114), glm::vec3(-60.000, 0.000, 0.000), glm::vec3(4.000, 2.000, 6.000), glm::vec3(0.424, 0.345, 0.294));
	createObject(glm::vec3(-11.000, 24.013, 27.088), glm::vec3(-30.000, 0.000, 0.000), glm::vec3(4.000, 2.000, 6.000), glm::vec3(0.424, 0.345, 0.294));
	createObject(glm::vec3(-11.000, 26.189, 32.343), glm::vec3(-15.000, 0.000, 0.000), glm::vec3(4.000, 2.000, 6.000), glm::vec3(0.424, 0.345, 0.294));
	createObject(glm::vec3(16.500, 15.646, 0.353), glm::vec3(45.000, 0.000, 0.000), glm::vec3(1.000, 4.000, 3.000), glm::vec3(0.388, 0.373, 0.384));
	createObject(glm::vec3(16.500, 15.646, 11.646), glm::vec3(-45.000, 0.000, 0.000), glm::vec3(1.000, 4.000, 3.000), glm::vec3(0.388, 0.373, 0.384));
	createObject(glm::vec3(-1.000, 27.750, 26.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(32.000, 0.500, 20.000), glm::vec3(0.424, 0.345, 0.294));
	createObject(glm::vec3(-1.000, 27.000, 25.750), glm::vec3(0.000, 0.000, 0.000), glm::vec3(31.000, 1.000, 19.500), glm::vec3(0.686, 0.580, 0.514));
	createObject(glm::vec3(-16.000, 29.500, 35.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(1.000, 3.000, 1.000), glm::vec3(0.388, 0.373, 0.384));
	createObject(glm::vec3(14.000, 29.500, 35.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(1.000, 3.000, 1.000), glm::vec3(0.388, 0.373, 0.384));
	createObject(glm::vec3(8.000, 29.500, 35.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(1.000, 3.000, 1.000), glm::vec3(0.388, 0.373, 0.384));
	createObject(glm::vec3(2.000, 29.500, 35.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(1.000, 3.000, 1.000), glm::vec3(0.388, 0.373, 0.384));
	createObject(glm::vec3(-4.000, 29.500, 35.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(1.000, 3.000, 1.000), glm::vec3(0.388, 0.373, 0.384));
	createObject(glm::vec3(-10.000, 29.500, 35.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(1.000, 3.000, 1.000), glm::vec3(0.388, 0.373, 0.384));
	createObject(glm::vec3(14.000, 29.500, 29.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(1.000, 3.000, 1.000), glm::vec3(0.388, 0.373, 0.384));
	createObject(glm::vec3(-16.000, 29.500, 29.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(1.000, 3.000, 1.000), glm::vec3(0.388, 0.373, 0.384));
	createObject(glm::vec3(14.000, 29.500, 23.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(1.000, 3.000, 1.000), glm::vec3(0.388, 0.373, 0.384));
	createObject(glm::vec3(-16.000, 29.500, 23.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(1.000, 3.000, 1.000), glm::vec3(0.388, 0.373, 0.384));
	createObject(glm::vec3(14.000, 29.500, 17.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(1.000, 3.000, 1.000), glm::vec3(0.388, 0.373, 0.384));
	createObject(glm::vec3(-16.000, 29.500, 17.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(1.000, 3.000, 1.000), glm::vec3(0.388, 0.373, 0.384));
	createObject(glm::vec3(-16.000, 30.500, 25.250), glm::vec3(0.000, 0.000, 0.000), glm::vec3(0.500, 0.500, 18.500), glm::vec3(0.686, 0.580, 0.514));
	createObject(glm::vec3(14.000, 30.500, 25.250), glm::vec3(0.000, 0.000, 0.000), glm::vec3(0.500, 0.500, 18.500), glm::vec3(0.686, 0.580, 0.514));
	createObject(glm::vec3(-1.000, 30.500, 35.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(29.000, 0.500, 0.500), glm::vec3(0.686, 0.580, 0.514));
	createObject(glm::vec3(-1.000, 34.000, -30.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(32.000, 20.000, 4.000), glm::vec3(0.745, 0.408, 0.384));
	createObject(glm::vec3(-1.000, 34.000, -10.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(32.000, 20.000, 12.000), glm::vec3(0.745, 0.408, 0.384));
	createObject(glm::vec3(0.500, 31.750, -22.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(29.000, 8.500, 12.000), glm::vec3(0.745, 0.408, 0.384));
	createObject(glm::vec3(-14.500, 32.000, -22.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(1.000, 8.000, 12.000), glm::vec3(0.067, 0.067, 0.067));
	createObject(glm::vec3(-15.500, 32.000, -22.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(1.000, 8.000, 1.000), glm::vec3(0.388, 0.373, 0.384));
	createObject(glm::vec3(-15.125, 32.000, -25.250), glm::vec3(0.000, 0.000, 0.000), glm::vec3(0.250, 0.500, 5.500), glm::vec3(0.388, 0.373, 0.384));
	createObject(glm::vec3(-15.250, 32.000, -25.250), glm::vec3(0.000, 0.000, 0.000), glm::vec3(0.500, 8.000, 0.500), glm::vec3(0.388, 0.373, 0.384));
	createObject(glm::vec3(-15.125, 34.500, -25.250), glm::vec3(0.000, 0.000, 0.000), glm::vec3(0.250, 0.500, 5.500), glm::vec3(0.388, 0.373, 0.384));
	createObject(glm::vec3(-15.125, 29.500, -25.250), glm::vec3(0.000, 0.000, 0.000), glm::vec3(0.250, 0.500, 5.500), glm::vec3(0.388, 0.373, 0.384));
	createObject(glm::vec3(-15.125, 34.500, -18.750), glm::vec3(0.000, 0.000, 0.000), glm::vec3(0.250, 0.500, 5.500), glm::vec3(0.388, 0.373, 0.384));
	createObject(glm::vec3(-15.125, 32.000, -18.750), glm::vec3(0.000, 0.000, 0.000), glm::vec3(0.250, 0.500, 5.500), glm::vec3(0.388, 0.373, 0.384));
	createObject(glm::vec3(-15.125, 29.500, -18.750), glm::vec3(0.000, 0.000, 0.000), glm::vec3(0.250, 0.500, 5.500), glm::vec3(0.388, 0.373, 0.384));
	createObject(glm::vec3(-15.250, 32.000, -18.750), glm::vec3(0.000, 0.000, 0.000), glm::vec3(0.500, 8.000, 0.500), glm::vec3(0.388, 0.373, 0.384));
	createObject(glm::vec3(-16.000, 27.750, -22.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(3.000, 0.500, 12.000), glm::vec3(0.388, 0.373, 0.384));
	createObject(glm::vec3(-1.000, 34.000, -4.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(40.000, 4.000, 8.000), glm::vec3(0.631, 0.769, 0.549));
	createObject(glm::vec3(-18.500, 42.000, -4.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(1.000, 12.000, 8.000), glm::vec3(0.067, 0.067, 0.067));
	createObject(glm::vec3(-18.500, 38.250, 8.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(1.000, 11.500, 8.000), glm::vec3(0.067, 0.067, 0.067));
	createObject(glm::vec3(-19.750, 42.250, -7.750), glm::vec3(0.000, 0.000, 0.000), glm::vec3(1.500, 11.500, 0.500), glm::vec3(0.424, 0.345, 0.294));
	createObject(glm::vec3(-19.750, 42.250, -0.250), glm::vec3(0.000, 0.000, 0.000), glm::vec3(1.500, 11.500, 0.500), glm::vec3(0.424, 0.345, 0.294));
	createObject(glm::vec3(-21.000, 36.250, -4.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(4.000, 0.500, 8.000), glm::vec3(0.424, 0.345, 0.294));
	createObject(glm::vec3(-21.875, 35.750, -7.250), glm::vec3(0.000, 0.000, 0.000), glm::vec3(1.250, 0.500, 0.500), glm::vec3(0.686, 0.580, 0.514));
	createObject(glm::vec3(-21.875, 35.750, -0.750), glm::vec3(0.000, 0.000, 0.000), glm::vec3(1.250, 0.500, 0.500), glm::vec3(0.686, 0.580, 0.514));
	createObject(glm::vec3(-21.875, 35.750, -4.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(1.250, 0.500, 0.500), glm::vec3(0.686, 0.580, 0.514));
	createObject(glm::vec3(-21.125, 35.500, -4.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(0.250, 1.000, 7.500), glm::vec3(0.424, 0.345, 0.294));
	createObject(glm::vec3(-19.750, 38.250, 4.250), glm::vec3(0.000, 0.000, 0.000), glm::vec3(1.500, 11.500, 0.500), glm::vec3(0.424, 0.345, 0.294));
	createObject(glm::vec3(-19.750, 38.250, 11.750), glm::vec3(0.000, 0.000, 0.000), glm::vec3(1.500, 11.500, 0.500), glm::vec3(0.424, 0.345, 0.294));
	createObject(glm::vec3(-21.750, 32.250, 8.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(0.500, 0.500, 8.000), glm::vec3(0.424, 0.345, 0.294));
	createObject(glm::vec3(-21.750, 35.250, 8.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(0.500, 0.500, 8.000), glm::vec3(0.424, 0.345, 0.294));
	createObject(glm::vec3(-21.750, 33.750, 4.250), glm::vec3(0.000, 0.000, 0.000), glm::vec3(0.250, 2.500, 0.250), glm::vec3(0.686, 0.580, 0.514));
	createObject(glm::vec3(-21.750, 33.750, 5.250), glm::vec3(0.000, 0.000, 0.000), glm::vec3(0.250, 2.500, 0.250), glm::vec3(0.686, 0.580, 0.514));
	createObject(glm::vec3(-21.750, 33.750, 6.250), glm::vec3(0.000, 0.000, 0.000), glm::vec3(0.250, 2.500, 0.250), glm::vec3(0.686, 0.580, 0.514));
	createObject(glm::vec3(-21.750, 33.750, 7.250), glm::vec3(0.000, 0.000, 0.000), glm::vec3(0.250, 2.500, 0.250), glm::vec3(0.686, 0.580, 0.514));
	createObject(glm::vec3(-21.750, 33.750, 8.250), glm::vec3(0.000, 0.000, 0.000), glm::vec3(0.250, 2.500, 0.250), glm::vec3(0.686, 0.580, 0.514));
	createObject(glm::vec3(-21.750, 33.750, 9.250), glm::vec3(0.000, 0.000, 0.000), glm::vec3(0.250, 2.500, 0.250), glm::vec3(0.686, 0.580, 0.514));
	createObject(glm::vec3(-21.750, 33.750, 10.250), glm::vec3(0.000, 0.000, 0.000), glm::vec3(0.250, 2.500, 0.250), glm::vec3(0.686, 0.580, 0.514));
	createObject(glm::vec3(-21.750, 33.750, 11.250), glm::vec3(0.000, 0.000, 0.000), glm::vec3(0.250, 2.500, 0.250), glm::vec3(0.686, 0.580, 0.514));
	createObject(glm::vec3(-21.750, 33.750, 11.750), glm::vec3(0.000, 0.000, 0.000), glm::vec3(0.250, 2.500, 0.250), glm::vec3(0.686, 0.580, 0.514));
	createObject(glm::vec3(-21.750, 33.750, 10.750), glm::vec3(0.000, 0.000, 0.000), glm::vec3(0.250, 2.500, 0.250), glm::vec3(0.686, 0.580, 0.514));
	createObject(glm::vec3(-21.750, 33.750, 9.750), glm::vec3(0.000, 0.000, 0.000), glm::vec3(0.250, 2.500, 0.250), glm::vec3(0.686, 0.580, 0.514));
	createObject(glm::vec3(-21.750, 33.750, 8.750), glm::vec3(0.000, 0.000, 0.000), glm::vec3(0.250, 2.500, 0.250), glm::vec3(0.686, 0.580, 0.514));
	createObject(glm::vec3(-21.750, 33.750, 7.750), glm::vec3(0.000, 0.000, 0.000), glm::vec3(0.250, 2.500, 0.250), glm::vec3(0.686, 0.580, 0.514));
	createObject(glm::vec3(-21.750, 33.750, 6.750), glm::vec3(0.000, 0.000, 0.000), glm::vec3(0.250, 2.500, 0.250), glm::vec3(0.686, 0.580, 0.514));
	createObject(glm::vec3(-21.750, 33.750, 5.750), glm::vec3(0.000, 0.000, 0.000), glm::vec3(0.250, 2.500, 0.250), glm::vec3(0.686, 0.580, 0.514));
	createObject(glm::vec3(-21.750, 33.750, 4.750), glm::vec3(0.000, 0.000, 0.000), glm::vec3(0.250, 2.500, 0.250), glm::vec3(0.686, 0.580, 0.514));
	createObject(glm::vec3(-21.250, 33.750, 4.250), glm::vec3(0.000, 0.000, 0.000), glm::vec3(0.250, 2.500, 0.250), glm::vec3(0.686, 0.580, 0.514));
	createObject(glm::vec3(-21.250, 33.750, 11.750), glm::vec3(0.000, 0.000, 0.000), glm::vec3(0.250, 2.500, 0.250), glm::vec3(0.686, 0.580, 0.514));
	createObject(glm::vec3(-21.000, 35.250, 4.250), glm::vec3(0.000, 0.000, 0.000), glm::vec3(1.000, 0.500, 0.500), glm::vec3(0.424, 0.345, 0.294));
	createObject(glm::vec3(-21.000, 35.250, 11.750), glm::vec3(0.000, 0.000, 0.000), glm::vec3(1.000, 0.500, 0.500), glm::vec3(0.424, 0.345, 0.294));
	createObject(glm::vec3(-19.250, 32.000, 8.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(4.500, 1.000, 8.000), glm::vec3(0.424, 0.345, 0.294));
	createObject(glm::vec3(16.000, 47.416, -23.598), glm::vec3(-15.000, 0.000, 0.000), glm::vec3(1.000, 0.250, 26.000), glm::vec3(0.388, 0.373, 0.384));
	createObject(glm::vec3(14.000, 47.416, -23.598), glm::vec3(-15.000, 0.000, 0.000), glm::vec3(1.000, 0.250, 26.000), glm::vec3(0.388, 0.373, 0.384));
	createObject(glm::vec3(12.000, 47.416, -23.598), glm::vec3(-15.000, 0.000, 0.000), glm::vec3(1.000, 0.250, 26.000), glm::vec3(0.388, 0.373, 0.384));
	createObject(glm::vec3(6.000, 47.416, -23.598), glm::vec3(-15.000, 0.000, 0.000), glm::vec3(1.000, 0.250, 26.000), glm::vec3(0.388, 0.373, 0.384));
	createObject(glm::vec3(10.000, 47.416, -23.598), glm::vec3(-15.000, 0.000, 0.000), glm::vec3(1.000, 0.250, 26.000), glm::vec3(0.388, 0.373, 0.384));
	createObject(glm::vec3(8.000, 47.416, -23.598), glm::vec3(-15.000, 0.000, 0.000), glm::vec3(1.000, 0.250, 26.000), glm::vec3(0.388, 0.373, 0.384));
	createObject(glm::vec3(-0.000, 47.416, -23.598), glm::vec3(-15.000, 0.000, 0.000), glm::vec3(1.000, 0.250, 26.000), glm::vec3(0.388, 0.373, 0.384));
	createObject(glm::vec3(4.000, 47.416, -23.598), glm::vec3(-15.000, 0.000, 0.000), glm::vec3(1.000, 0.250, 26.000), glm::vec3(0.388, 0.373, 0.384));
	createObject(glm::vec3(2.000, 47.416, -23.598), glm::vec3(-15.000, 0.000, 0.000), glm::vec3(1.000, 0.250, 26.000), glm::vec3(0.388, 0.373, 0.384));
	createObject(glm::vec3(-6.000, 47.416, -23.598), glm::vec3(-15.000, 0.000, 0.000), glm::vec3(1.000, 0.250, 26.000), glm::vec3(0.388, 0.373, 0.384));
	createObject(glm::vec3(-2.000, 47.416, -23.598), glm::vec3(-15.000, 0.000, 0.000), glm::vec3(1.000, 0.250, 26.000), glm::vec3(0.388, 0.373, 0.384));
	createObject(glm::vec3(-4.000, 47.416, -23.598), glm::vec3(-15.000, 0.000, 0.000), glm::vec3(1.000, 0.250, 26.000), glm::vec3(0.388, 0.373, 0.384));
	createObject(glm::vec3(-12.000, 47.416, -23.598), glm::vec3(-15.000, 0.000, 0.000), glm::vec3(1.000, 0.250, 26.000), glm::vec3(0.388, 0.373, 0.384));
	createObject(glm::vec3(-8.000, 47.416, -23.598), glm::vec3(-15.000, 0.000, 0.000), glm::vec3(1.000, 0.250, 26.000), glm::vec3(0.388, 0.373, 0.384));
	createObject(glm::vec3(-10.000, 47.416, -23.598), glm::vec3(-15.000, 0.000, 0.000), glm::vec3(1.000, 0.250, 26.000), glm::vec3(0.388, 0.373, 0.384));
	createObject(glm::vec3(-18.000, 47.416, -23.598), glm::vec3(-15.000, 0.000, 0.000), glm::vec3(1.000, 0.250, 26.000), glm::vec3(0.388, 0.373, 0.384));
	createObject(glm::vec3(-14.000, 47.416, -23.598), glm::vec3(-15.000, 0.000, 0.000), glm::vec3(1.000, 0.250, 26.000), glm::vec3(0.388, 0.373, 0.384));
	createObject(glm::vec3(-16.000, 47.416, -23.598), glm::vec3(-15.000, 0.000, 0.000), glm::vec3(1.000, 0.250, 26.000), glm::vec3(0.388, 0.373, 0.384));
	createObject(glm::vec3(-6.500, 34.000, 24.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(1.000, 12.000, 8.000), glm::vec3(0.067, 0.067, 0.067));
	createObject(glm::vec3(-8.125, 34.000, 20.125), glm::vec3(0.000, 0.000, 0.000), glm::vec3(2.250, 12.000, 0.250), glm::vec3(0.424, 0.345, 0.294));
	createObject(glm::vec3(-8.125, 34.000, 27.875), glm::vec3(0.000, 0.000, 0.000), glm::vec3(2.250, 12.000, 0.250), glm::vec3(0.424, 0.345, 0.294));
	createObject(glm::vec3(-8.125, 39.875, 24.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(2.250, 0.250, 7.500), glm::vec3(0.424, 0.345, 0.294));
	createObject(glm::vec3(0.500, 34.000, 24.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(13.000, 12.000, 8.000), glm::vec3(0.431, 0.600, 0.792));
	createObject(glm::vec3(-1.000, 36.000, 30.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(16.000, 16.000, 4.000), glm::vec3(0.431, 0.600, 0.792));
	createObject(glm::vec3(-21.619, 42.869, 12.500), glm::vec3(0.000, 0.000, -45.000), glm::vec3(2.750, 0.500, 0.500), glm::vec3(0.388, 0.373, 0.384));
	createObject(glm::vec3(-21.619, 42.869, 3.500), glm::vec3(0.000, 0.000, -45.000), glm::vec3(2.750, 0.500, 0.500), glm::vec3(0.388, 0.373, 0.384));
	createObject(glm::vec3(-22.208, 43.926, 3.500), glm::vec3(0.000, 0.000, 15.000), glm::vec3(3.500, 0.500, 1.000), glm::vec3(0.588, 0.333, 0.333));
	createObject(glm::vec3(-22.208, 43.926, 5.500), glm::vec3(0.000, 0.000, 15.000), glm::vec3(3.500, 0.500, 1.000), glm::vec3(0.588, 0.333, 0.333));
	createObject(glm::vec3(-22.208, 43.926, 7.500), glm::vec3(0.000, 0.000, 15.000), glm::vec3(3.500, 0.500, 1.000), glm::vec3(0.588, 0.333, 0.333));
	createObject(glm::vec3(-22.208, 43.926, 9.500), glm::vec3(0.000, 0.000, 15.000), glm::vec3(3.500, 0.500, 1.000), glm::vec3(0.588, 0.333, 0.333));
	createObject(glm::vec3(-22.208, 43.926, 11.500), glm::vec3(0.000, 0.000, 15.000), glm::vec3(3.500, 0.500, 1.000), glm::vec3(0.588, 0.333, 0.333));
	createObject(glm::vec3(-22.208, 43.926, 12.500), glm::vec3(0.000, 0.000, 15.000), glm::vec3(3.500, 0.500, 1.000), glm::vec3(0.804, 0.804, 0.804));
	createObject(glm::vec3(-22.208, 43.926, 10.500), glm::vec3(0.000, 0.000, 15.000), glm::vec3(3.500, 0.500, 1.000), glm::vec3(0.804, 0.804, 0.804));
	createObject(glm::vec3(-22.208, 43.926, 8.500), glm::vec3(0.000, 0.000, 15.000), glm::vec3(3.500, 0.500, 1.000), glm::vec3(0.804, 0.804, 0.804));
	createObject(glm::vec3(-22.208, 43.926, 6.500), glm::vec3(0.000, 0.000, 15.000), glm::vec3(3.500, 0.500, 1.000), glm::vec3(0.804, 0.804, 0.804));
	createObject(glm::vec3(-22.208, 43.926, 4.500), glm::vec3(0.000, 0.000, 15.000), glm::vec3(3.500, 0.500, 1.000), glm::vec3(0.804, 0.804, 0.804));
	createObject(glm::vec3(-1.000, 10.000, -8.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(32.000, 20.000, 8.000), glm::vec3(0.827, 0.745, 0.588));
	createObject(glm::vec3(-17.134, 21.768, -18.000), glm::vec3(0.000, 0.000, -30.000), glm::vec3(2.000, 4.000, 28.000), glm::vec3(0.424, 0.345, 0.294));
	createObject(glm::vec3(9.000, 10.783, 16.937), glm::vec3(-75.000, 0.000, 0.000), glm::vec3(4.000, 2.000, 6.000), glm::vec3(0.424, 0.345, 0.294));
	createObject(glm::vec3(-11.000, 16.038, 19.114), glm::vec3(-60.000, 0.000, 0.000), glm::vec3(4.000, 2.000, 6.000), glm::vec3(0.424, 0.345, 0.294));
	createObject(glm::vec3(-11.000, 20.550, 22.576), glm::vec3(-45.000, 0.000, 0.000), glm::vec3(4.000, 2.000, 6.000), glm::vec3(0.424, 0.345, 0.294));
	createObject(glm::vec3(-1.000, 10.000, -26.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(32.000, 20.000, 12.000), glm::vec3(0.827, 0.745, 0.588));
	createObject(glm::vec3(-1.000, 18.000, -16.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(32.000, 4.000, 8.000), glm::vec3(0.827, 0.745, 0.588));
	createObject(glm::vec3(1.000, 16.000, -0.000), glm::vec3(45.000, 0.000, 0.000), glm::vec3(34.000, 2.000, 2.000), glm::vec3(0.510, 0.490, 0.580));
	createObject(glm::vec3(1.000, 16.000, 12.000), glm::vec3(-45.000, 0.000, 0.000), glm::vec3(34.000, 2.000, 2.000), glm::vec3(0.510, 0.490, 0.580));
	createObject(glm::vec3(1.000, 15.646, 11.646), glm::vec3(-45.000, 0.000, 0.000), glm::vec3(1.000, 4.000, 3.000), glm::vec3(0.388, 0.373, 0.384));
	createObject(glm::vec3(1.000, 15.646, 0.353), glm::vec3(45.000, 0.000, 0.000), glm::vec3(1.000, 4.000, 3.000), glm::vec3(0.388, 0.373, 0.384));
	createObject(glm::vec3(1.000, 17.000, 6.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(38.000, 2.000, 22.000), glm::vec3(0.388, 0.373, 0.384));
	createObject(glm::vec3(1.000, 8.500, -2.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(37.000, 15.000, 4.000), glm::vec3(0.388, 0.373, 0.384));
	createObject(glm::vec3(0.500, 8.000, -16.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(29.000, 16.000, 8.000), glm::vec3(0.827, 0.745, 0.588));
	createObject(glm::vec3(1.000, 8.500, 14.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(37.000, 15.000, 4.000), glm::vec3(0.388, 0.373, 0.384));
	createObject(glm::vec3(-11.000, 10.783, 16.937), glm::vec3(-75.000, 0.000, 0.000), glm::vec3(4.000, 2.000, 6.000), glm::vec3(0.424, 0.345, 0.294));
	createObject(glm::vec3(-11.000, 4.500, 17.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(5.000, 7.000, 2.000), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(9.000, 4.500, 17.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(5.000, 7.000, 2.000), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(-19.000, 3.750, -20.500), glm::vec3(0.000, 0.000, 0.000), glm::vec3(4.000, 0.500, 1.000), glm::vec3(0.388, 0.373, 0.384));
	createObject(glm::vec3(-19.000, 3.750, -11.500), glm::vec3(0.000, 0.000, 0.000), glm::vec3(4.000, 0.500, 1.000), glm::vec3(0.388, 0.373, 0.384));
	createObject(glm::vec3(-15.250, 8.500, -16.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(0.500, 15.000, 1.000), glm::vec3(0.388, 0.373, 0.384));
	createObject(glm::vec3(-15.125, 12.000, -16.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(0.250, 0.500, 8.000), glm::vec3(0.388, 0.373, 0.384));
	createObject(glm::vec3(-15.125, 8.000, -16.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(0.250, 0.500, 8.000), glm::vec3(0.388, 0.373, 0.384));
	createObject(glm::vec3(-15.125, 4.000, -16.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(0.250, 0.500, 8.000), glm::vec3(0.388, 0.373, 0.384));
	createObject(glm::vec3(-18.208, 15.926, -16.000), glm::vec3(0.000, 0.000, 15.000), glm::vec3(3.500, 0.500, 10.000), glm::vec3(0.424, 0.345, 0.294));
	createObject(glm::vec3(-17.619, 14.869, -11.500), glm::vec3(0.000, 0.000, -45.000), glm::vec3(2.750, 0.500, 0.500), glm::vec3(0.388, 0.373, 0.384));
	createObject(glm::vec3(-17.619, 14.869, -20.500), glm::vec3(0.000, 0.000, -45.000), glm::vec3(2.750, 0.500, 0.500), glm::vec3(0.388, 0.373, 0.384));
	createObject(glm::vec3(-14.500, 15.646, 0.353), glm::vec3(45.000, 0.000, 0.000), glm::vec3(1.000, 4.000, 3.000), glm::vec3(0.388, 0.373, 0.384));
	createObject(glm::vec3(-14.500, 15.646, 11.646), glm::vec3(-45.000, 0.000, 0.000), glm::vec3(1.000, 4.000, 3.000), glm::vec3(0.388, 0.373, 0.384));
	createObject(glm::vec3(-14.500, 8.000, -16.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(1.000, 16.000, 8.000), glm::vec3(0.067, 0.067, 0.067));
	createObject(glm::vec3(-15.400, 2.250, -2.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(4.700, 2.400, 4.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(-16.400, 4.750, -2.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(2.700, 2.400, 4.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(-15.400, 7.250, -2.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(4.700, 2.400, 4.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(-16.400, 9.750, -2.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(2.700, 2.400, 4.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(-15.400, 12.250, -2.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(4.700, 2.400, 4.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(-16.400, 14.750, -2.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(2.700, 2.400, 4.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(-11.000, 2.250, -2.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(3.900, 2.400, 4.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(-13.000, 4.750, -2.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(3.900, 2.400, 4.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(-11.000, 7.250, -2.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(3.900, 2.400, 4.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(-13.000, 9.750, -2.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(3.900, 2.400, 4.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(-11.000, 12.250, -2.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(3.900, 2.400, 4.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(-13.000, 14.750, -2.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(3.900, 2.400, 4.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(-9.000, 14.750, -2.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(3.900, 2.400, 4.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(-7.000, 12.250, -2.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(3.900, 2.400, 4.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(-9.000, 9.750, -2.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(3.900, 2.400, 4.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(-7.000, 7.250, -2.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(3.900, 2.400, 4.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(-9.000, 4.750, -2.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(3.900, 2.400, 4.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(-7.000, 2.250, -2.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(3.900, 2.400, 4.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(-5.000, 4.750, -2.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(3.900, 2.400, 4.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(-5.000, 9.750, -2.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(3.900, 2.400, 4.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(-5.000, 14.750, -2.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(3.900, 2.400, 4.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(-3.000, 12.250, -2.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(3.900, 2.400, 4.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(-3.000, 7.250, -2.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(3.900, 2.400, 4.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(-3.000, 2.250, -2.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(3.900, 2.400, 4.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(-1.000, 4.750, -2.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(3.900, 2.400, 4.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(-1.000, 9.750, -2.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(3.900, 2.400, 4.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(-1.000, 14.750, -2.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(3.900, 2.400, 4.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(1.000, 12.250, -2.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(3.900, 2.400, 4.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(3.000, 9.750, -2.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(3.900, 2.400, 4.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(1.000, 7.250, -2.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(3.900, 2.400, 4.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(3.000, 4.750, -2.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(3.900, 2.400, 4.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(1.000, 2.250, -2.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(3.900, 2.400, 4.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(3.000, 14.750, -2.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(3.900, 2.400, 4.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(7.000, 14.750, -2.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(3.900, 2.400, 4.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(5.000, 12.250, -2.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(3.900, 2.400, 4.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(7.000, 9.750, -2.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(3.900, 2.400, 4.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(5.000, 7.250, -2.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(3.900, 2.400, 4.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(7.000, 4.750, -2.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(3.900, 2.400, 4.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(5.000, 2.250, -2.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(3.900, 2.400, 4.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(9.000, 2.250, -2.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(3.900, 2.400, 4.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(11.000, 4.750, -2.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(3.900, 2.400, 4.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(9.000, 7.250, -2.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(3.900, 2.400, 4.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(11.000, 9.750, -2.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(3.900, 2.400, 4.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(9.000, 12.250, -2.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(3.900, 2.400, 4.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(11.000, 14.750, -2.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(3.900, 2.400, 4.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(15.000, 14.750, -2.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(3.900, 2.400, 4.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(13.000, 12.250, -2.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(3.900, 2.400, 4.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(15.000, 9.750, -2.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(3.900, 2.400, 4.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(13.000, 7.250, -2.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(3.900, 2.400, 4.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(15.000, 4.750, -2.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(3.900, 2.400, 4.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(13.000, 2.250, -2.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(3.900, 2.400, 4.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(17.400, 2.250, -2.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(4.700, 2.400, 4.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(18.400, 4.750, -2.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(2.700, 2.400, 4.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(17.400, 7.250, -2.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(4.700, 2.400, 4.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(18.400, 9.750, -2.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(2.700, 2.400, 4.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(17.400, 12.250, -2.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(4.700, 2.400, 4.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(18.400, 14.750, -2.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(2.700, 2.400, 4.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(17.400, 2.250, 14.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(4.700, 2.400, 4.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(18.400, 4.750, 14.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(2.700, 2.400, 4.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(17.400, 7.250, 14.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(4.700, 2.400, 4.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(18.400, 9.750, 14.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(2.700, 2.400, 4.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(17.400, 12.250, 14.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(4.700, 2.400, 4.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(18.400, 14.750, 14.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(2.700, 2.400, 4.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(15.000, 4.750, 14.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(3.900, 2.400, 4.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(15.000, 9.750, 14.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(3.900, 2.400, 4.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(15.000, 14.750, 14.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(3.900, 2.400, 4.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(13.000, 12.250, 14.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(3.900, 2.400, 4.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(13.000, 7.250, 14.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(3.900, 2.400, 4.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(13.000, 2.250, 14.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(3.900, 2.400, 4.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(11.000, 4.750, 14.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(3.900, 2.400, 4.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(11.000, 9.750, 14.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(3.900, 2.400, 4.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(11.000, 14.750, 14.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(3.900, 2.400, 4.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(9.000, 12.250, 14.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(3.900, 2.400, 4.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(9.000, 7.250, 14.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(3.900, 2.400, 4.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(9.000, 2.250, 14.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(3.900, 2.400, 4.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(7.000, 4.750, 14.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(3.900, 2.400, 4.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(7.000, 9.750, 14.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(3.900, 2.400, 4.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(7.000, 14.750, 14.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(3.900, 2.400, 4.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(5.000, 12.250, 14.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(3.900, 2.400, 4.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(5.000, 7.250, 14.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(3.900, 2.400, 4.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(5.000, 2.250, 14.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(3.900, 2.400, 4.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(3.000, 4.750, 14.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(3.900, 2.400, 4.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(3.000, 9.750, 14.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(3.900, 2.400, 4.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(3.000, 14.750, 14.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(3.900, 2.400, 4.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(1.000, 12.250, 14.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(3.900, 2.400, 4.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(1.000, 7.250, 14.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(3.900, 2.400, 4.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(1.000, 2.250, 14.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(3.900, 2.400, 4.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(-1.000, 4.750, 14.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(3.900, 2.400, 4.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(-1.000, 9.750, 14.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(3.900, 2.400, 4.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(-1.000, 14.750, 14.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(3.900, 2.400, 4.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(-3.000, 12.250, 14.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(3.900, 2.400, 4.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(-3.000, 7.250, 14.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(3.900, 2.400, 4.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(-3.000, 2.250, 14.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(3.900, 2.400, 4.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(-5.000, 4.750, 14.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(3.900, 2.400, 4.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(-5.000, 9.750, 14.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(3.900, 2.400, 4.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(-5.000, 14.750, 14.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(3.900, 2.400, 4.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(-7.000, 12.250, 14.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(3.900, 2.400, 4.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(-7.000, 7.250, 14.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(3.900, 2.400, 4.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(-7.000, 2.250, 14.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(3.900, 2.400, 4.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(-9.000, 4.750, 14.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(3.900, 2.400, 4.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(-9.000, 9.750, 14.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(3.900, 2.400, 4.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(-9.000, 14.750, 14.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(3.900, 2.400, 4.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(-11.000, 12.250, 14.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(3.900, 2.400, 4.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(-11.000, 7.250, 14.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(3.900, 2.400, 4.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(-11.000, 2.250, 14.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(3.900, 2.400, 4.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(-13.000, 4.750, 14.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(3.900, 2.400, 4.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(-13.000, 9.750, 14.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(3.900, 2.400, 4.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(-13.000, 14.750, 14.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(3.900, 2.400, 4.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(-15.400, 12.250, 14.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(4.700, 2.400, 4.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(-15.400, 7.250, 14.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(4.700, 2.400, 4.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(-15.400, 2.250, 14.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(4.700, 2.400, 4.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(-16.400, 4.750, 14.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(2.700, 2.400, 4.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(-16.400, 9.750, 14.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(2.700, 2.400, 4.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(-16.400, 14.750, 14.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(2.700, 2.400, 4.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(1.000, 0.500, -2.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(38.000, 1.000, 5.000), glm::vec3(0.388, 0.373, 0.384));
	createObject(glm::vec3(1.000, 0.500, 14.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(38.000, 1.000, 5.000), glm::vec3(0.388, 0.373, 0.384));
	createObject(glm::vec3(9.000, 0.500, 17.500), glm::vec3(0.000, 0.000, 0.000), glm::vec3(6.000, 1.000, 2.000), glm::vec3(0.388, 0.373, 0.384));
	createObject(glm::vec3(-11.000, 0.500, 17.500), glm::vec3(0.000, 0.000, 0.000), glm::vec3(6.000, 1.000, 2.000), glm::vec3(0.388, 0.373, 0.384));
	createObject(glm::vec3(-21.500, 2.250, -16.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(0.500, 2.500, 9.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(-18.500, 0.500, -16.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(7.000, 1.000, 10.000), glm::vec3(0.388, 0.373, 0.384));
	createObject(glm::vec3(-19.125, 2.250, -11.500), glm::vec3(0.000, 0.000, 0.000), glm::vec3(4.250, 2.500, 0.500), glm::vec3(0.639, 0.635, 0.647));
	createObject(glm::vec3(-21.500, 3.750, -16.000), glm::vec3(0.000, 0.000, 0.000), glm::vec3(1.000, 0.500, 10.000), glm::vec3(0.388, 0.373, 0.384));
	createObject(glm::vec3(-19.125, 2.250, -20.500), glm::vec3(0.000, 0.000, 0.000), glm::vec3(4.250, 2.500, 0.500), glm::vec3(0.639, 0.635, 0.647));
}