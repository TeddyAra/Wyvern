#include "World.h"

#include <iostream>

World::World() 
	: debug(0.0f), camera(std::make_shared<Camera>(60)), controller(std::make_shared<CameraController>(camera))
{

}

World::~World() {

}

std::shared_ptr<Camera> World::getCamera() {
	return camera;
}

void World::updateCamera() {
	controller->update(1.0f);
}

float World::getDebug() {
	return debug;
}

void World::setDebug(float debug) {
	this->debug = debug;
	std::cout << "Debug float changed to " << debug << std::endl;
}