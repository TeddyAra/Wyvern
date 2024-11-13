#include "World.h"

World::World() 
	: selected(1) 
{

}

World::~World() {

}

int World::getSelected() {
	return selected;
}