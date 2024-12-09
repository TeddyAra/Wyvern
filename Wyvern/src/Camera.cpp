#include "Camera.h"

#include <iostream>

#include "Input.h"

Camera::Camera(float fov)
	: position(glm::vec3(0, 0, -5)), rotation(glm::vec3(0, 0, 0)), 
	front(glm::vec3(0, 0, 1)), up(glm::vec3(0, 1, 0)), right(glm::vec3(1, 0, 0)),
	fov(fov)
{

}

Camera::~Camera() {

}

glm::vec3 Camera::getPosition() {
	return position;
}

void Camera::setPosition(float x, float y, float z) {
	position = glm::vec3(x, y, z);
}

void Camera::setPosition(glm::vec3 position) {
	this->position = position;
}

void Camera::translate(float x, float y, float z) {
	position += glm::vec3(x, y, z);
}

void Camera::translate(glm::vec3 translation) {
	position += translation;
}

glm::vec3 Camera::getRotation() {
	return rotation;
}

void Camera::setRotation(float x, float y, float z) {
	rotation = glm::vec3(x, y, z);
}

void Camera::setRotation(glm::vec3 rotation) {
	this->rotation = rotation;
}

void Camera::setYaw(float yaw) {
	rotation.y = yaw;
}

void Camera::setPitch(float pitch) {
	rotation.x = pitch;
}

void Camera::rotate(float x, float y, float z) {
	rotation += glm::vec3(x, y, z);
}

void Camera::rotate(glm::vec3 rotation) {
	this->rotation += rotation;
}

void Camera::updateTransform() {
	front.x = cos(glm::radians(rotation.y)) * cos(glm::radians(rotation.x));
	front.y = sin(glm::radians(rotation.x));
	front.z = sin(glm::radians(rotation.y)) * cos(glm::radians(rotation.x));
	front = glm::normalize(front);

	right = glm::cross(front, glm::vec3(0, 1, 0));
	right = glm::normalize(right);

	up = glm::cross(right, front);
	up = glm::normalize(up);
}

glm::mat4 Camera::getViewMatrix() {
	glm::vec2 delta = Input::getDeltaMousePosition();
	//rotate(delta.y, -delta.x, 0);
	updateTransform();
	return glm::lookAt(position, position + front, -up);
}

void Camera::setFov(float fov) {
	this->fov = fov;
}

float Camera::getFov() {
	return fov;
}

glm::vec3 Camera::getFront() {
	return front;
}

glm::vec3 Camera::getRight() {
	return right;
}

glm::vec3 Camera::getUp() {
	return up;
}