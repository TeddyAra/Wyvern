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
	return glm::lookAt(position, position + front, -up);
}

void Camera::setFov(float fov) {
	this->fov = fov;
}

float Camera::getFov() {
	return fov;
}