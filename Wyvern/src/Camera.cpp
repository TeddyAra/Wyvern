#include "Camera.h"

#include <iostream>

#include "Input.h"

Camera::Camera(float fov)
	: fov(fov)
{

}

Camera::~Camera() {

}

glm::mat4 Camera::getViewMatrix() {
	return glm::lookAt(position, position + front, glm::vec3(0.0f, -1.0f, 0.0f));
}

glm::mat4 Camera::getProjectionMatrix(glm::vec2 viewportSize) {
	return glm::perspective(glm::radians(fov), viewportSize.x / viewportSize.y, 0.1f, 500.0f);
}

void Camera::setFov(float fov) {
	this->fov = fov;
}

float Camera::getFov() {
	return fov;
}