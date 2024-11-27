#include "World.h"

#include <iostream>

World::World() 
	: debug(0.0f) 
{

}

World::~World() {

}

float World::getDebug() {
	return debug;
}

void World::setDebug(float debug) {
	this->debug = debug;
	std::cout << "Debug float changed to " << debug << std::endl;
}