#include "InteractionController.h"

InteractionController::InteractionController() 
	: world(std::make_unique<World>()) {

}

InteractionController::~InteractionController() {

}

int InteractionController::getSelected() {
	return world->getSelected();
}