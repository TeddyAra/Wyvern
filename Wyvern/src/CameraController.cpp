#include "CameraController.h"

CameraController::CameraController(std::shared_ptr<Camera> camera)
	: camera(camera)
{ 

}

CameraController::~CameraController() {

}

void CameraController::update(float deltaTime) {
	glm::vec3 translation = glm::vec3(0, 0, 0);
	float speed = (Input::getKey(GLFW_KEY_LEFT_SHIFT) ? fastSpeed : slowSpeed);

	if (Input::getKey(GLFW_KEY_D)) translation += camera->getRight() * speed;
	if (Input::getKey(GLFW_KEY_A)) translation -= camera->getRight() * speed;
	if (Input::getKey(GLFW_KEY_E)) translation += camera->getUp() * speed;
	if (Input::getKey(GLFW_KEY_Q)) translation -= camera->getUp() * speed;
	if (Input::getKey(GLFW_KEY_W)) translation += camera->getFront() * speed;
	if (Input::getKey(GLFW_KEY_S)) translation -= camera->getFront() * speed;

	camera->translate(translation);
}