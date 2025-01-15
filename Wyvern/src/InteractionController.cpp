#include "InteractionController.h"

#include "World.h"
#include "HistoryManager.h"

InteractionController::InteractionController(std::shared_ptr<World> world) 
	: world(world), history(std::make_unique<HistoryManager>()) 
{

}

InteractionController::~InteractionController() {

}

std::shared_ptr<Camera> InteractionController::getCamera() {
	return world->getCamera();
}

void InteractionController::toggleMoveSnap(bool value) {
	world->toggleMoveSnap(value);
}

void InteractionController::toggleRotationSnap(bool value) {
	world->toggleRotationSnap(value);
}

void InteractionController::setMoveSnap(float snap) {
	world->setMoveSnap(snap);
}

void InteractionController::setRotationSnap(float snap) {
	world->setRotationSnap(snap);
}

float InteractionController::getMoveSnap() {
	return world->getMoveSnap();
}

float InteractionController::getRotationSnap() {
	return world->getRotationSnap();
}

void InteractionController::addObject(std::shared_ptr<Transform> object) {
	world->addObject(object);
}

void InteractionController::changeTool(TransformTools::Tool tool) {
	world->changeTool(tool);
}

std::vector<std::shared_ptr<Transform>>& InteractionController::getObjects() {
	return world->getObjects();
}

std::vector<std::shared_ptr<Transform>>& InteractionController::getSelected() {
	return world->getSelected();
}

std::vector<std::shared_ptr<Transform>>& InteractionController::getTransformTools() {
	return world->getTransformTools();
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