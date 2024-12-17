#include "InteractionController.h"

#include "World.h"
#include "HistoryManager.h"

InteractionController::InteractionController(std::shared_ptr<World> world) 
	: world(world), history(std::make_unique<HistoryManager>()) 
{

}

InteractionController::~InteractionController() {

}

float InteractionController::getDebug() {
	return world->getDebug();
}

void InteractionController::setDebug(float debug) {
	world->setDebug(debug);
}

void InteractionController::createObject() {
	world->createObject();
}

void InteractionController::addToHistory(std::shared_ptr<ICommand> command) {
	history->addCommand(command);
}

void InteractionController::undo() {
	history->undo();
}

void InteractionController::redo() {
	history->redo();
}