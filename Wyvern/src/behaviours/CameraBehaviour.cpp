#include "CameraBehaviour.h"

#include "Transform.h"

void CameraBehaviour::start(Transform& transform) {
	
}

void CameraBehaviour::update(Transform& transform) {
	glm::vec3 translation = glm::vec3(0, 0, 0);
	float speed = (Input::getKey(GLFW_KEY_LEFT_SHIFT) ? fastSpeed : slowSpeed);

	if (Input::getKey(GLFW_KEY_D)) translation += transform.getRight() * speed;
	if (Input::getKey(GLFW_KEY_A)) translation -= transform.getRight() * speed;
	if (Input::getKey(GLFW_KEY_E)) translation += transform.getUp() * speed;
	if (Input::getKey(GLFW_KEY_Q)) translation -= transform.getUp() * speed;
	if (Input::getKey(GLFW_KEY_W)) translation += transform.getFront() * speed;
	if (Input::getKey(GLFW_KEY_S)) translation -= transform.getFront() * speed;

	transform.translate(translation);

	if (Input::getMouse(1)) {
		glm::vec2 mouseDelta = Input::getDeltaMousePosition();
		transform.rotateAroundAxis(transform.getRight(), mouseDelta.y);
		transform.rotateAroundAxis(glm::vec3(0, 1, 0), mouseDelta.x);
	}
}