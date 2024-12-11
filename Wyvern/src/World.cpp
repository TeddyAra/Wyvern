#include "World.h"

#include <iostream>

#include "CameraBehaviour.h"

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

	for (std::shared_ptr<Transform> object : objects) {
		object->update();
	}
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