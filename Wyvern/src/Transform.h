#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/quaternion.hpp"

#include <memory>

#include "Behaviour.h"
#include "Collider.h"
#include "BoxCollider.h"

class Transform {
public:
	Transform() 
		: position(glm::vec3(0, 0, 0)), rotation(glm::quat(glm::vec3(0, 0, 0))), scale(glm::vec3(1, 1, 1)), origin(glm::vec3(0.0f, 0.0f, 0.0f)), 
		front(glm::vec3(0, 0, 1)), right(glm::vec3(1, 0, 0)), up(glm::vec3(0, 1, 0)), 
		collider(std::make_shared<BoxCollider>()), colour(glm::vec3(0.9f, 0.9f, 0.9f)) {}
	virtual ~Transform() = default;

	// Collider
	void setCollider(std::shared_ptr<Collider> collider) {
		this->collider = collider;
	}

	std::shared_ptr<Collider> getCollider() {
		return collider;
	}

	// Position
	glm::vec3 getPosition() {
		return position;
	}

	void setPosition(float x, float y, float z) {
		position = glm::vec3(x, y, z);
	}

	void setPosition(glm::vec3 position) {
		this->position = position;
	}

	void translate(float x, float y, float z) {
		position += glm::vec3(x, y, z);
	}

	void translate(glm::vec3 translation) {
		position += translation;
	}

	void snapPosition(float snapping) {
		for (int axis = 0; axis < 3; axis++) {
			float remainder = fmod(position[axis], snapping);
			if (remainder < snapping / 2) {
				position[axis] -= remainder;
			} else {
				position[axis] += -remainder + snapping;
			}
		}
	}

	void snapRotation(float snapping) {
		glm::vec3 euler = getEulerRotation();
		for (int axis = 0; axis < 3; axis++) {
			float remainder = fmod(euler[axis], snapping);
			if (remainder < snapping / 2) {
				euler[axis] -= remainder;
			} else {
				euler[axis] += -remainder + snapping;
			}
		}
		setRotation(euler);
	}

	// Rotation
	glm::quat getRotation() {
		return rotation;
	}

	glm::vec3 getEulerRotation() {
		return glm::degrees(glm::eulerAngles(rotation));
	}

	void setRotation(float x, float y, float z) {
		glm::vec3 eulerRadians = glm::radians(glm::vec3(x, y, z));
		rotation = glm::quat(eulerRadians);

		updateDirectionVectors();
	}

	void setRotation(glm::vec3 eulerAngles) {
		glm::vec3 eulerRadians = glm::radians(eulerAngles);
		rotation = glm::quat(eulerRadians);

		updateDirectionVectors();
	}

	void setRotation(glm::quat quaternion) {
		rotation = quaternion;

		updateDirectionVectors();
	}

	void rotate(float x, float y, float z) {
		glm::vec3 angleRadians = glm::radians(glm::vec3(x, y, z));
		glm::quat quaternion = glm::quat(angleRadians);
		rotation = quaternion * rotation;
		rotation = glm::normalize(rotation);

		updateDirectionVectors();
	}

	void rotate(glm::vec3 eulerAngles) {
		glm::vec3 angleRadians = glm::radians(eulerAngles);
		glm::quat quaternion = glm::quat(angleRadians);
		rotation = quaternion * rotation;
		rotation = glm::normalize(rotation);

		updateDirectionVectors();
	}

	void rotateAroundAxis(glm::vec3 axis, float angle) {
		glm::vec3 normalizedAxis = glm::normalize(axis);
		float angleRadians = glm::radians(angle);
		glm::quat axisAngleRotation = glm::angleAxis(angleRadians, normalizedAxis);
		rotation = axisAngleRotation * rotation;
		rotation = glm::normalize(rotation);

		updateDirectionVectors();
	}

	void lookAt(glm::vec3 target) {
		glm::vec3 forward = glm::normalize(target - position);

		if (glm::length(forward) < 1e-6f) {
			return;
		}

		glm::vec3 up = glm::abs(forward.y) > 0.99f ? glm::vec3(0.0f, 0.0f, 1.0f) : glm::vec3(0.0f, 1.0f, 0.0f);
		glm::vec3 right = glm::normalize(glm::cross(up, forward));
		glm::vec3 correctedUp = glm::cross(forward, right);

		glm::mat3 rotationMatrix = glm::mat3(right, correctedUp, forward);
		rotation = glm::quat_cast(rotationMatrix);
		updateDirectionVectors();
	}

	// Scale
	glm::vec3 getScale() {
		return scale;
	}

	void setScale(float x, float y, float z) {
		scale = glm::vec3(x, y, z);
	}

	void setScale(glm::vec3 scale) {
		this->scale = scale;
	}

	void multiplyScale(float x, float y, float z) {
		glm::vec3 newScale = glm::vec3(scale.x * x, scale.y * y, scale.z * z);
		scale = newScale;
	}

	void multiplyScale(glm::vec3 scale) {
		glm::vec3 newScale = glm::vec3(this->scale.x * scale.x, this->scale.y * scale.y, this->scale.z * scale.z);
		this->scale = newScale;
	}

	// Origin
	glm::vec3 getOrigin() {
		return origin;
	}

	void setOrigin(float x, float y, float z) {
		origin = glm::vec3(x, y, z);
	}

	void setOrigin(glm::vec3 origin) {
		this->origin = origin;
	}

	void translateOrigin(float x, float y, float z) {
		origin += glm::vec3(x, y, z);
	}

	void translateOrigin(glm::vec3 translation) {
		origin += translation;
	}

	// Direction vectors
	glm::vec3 getFront() {
		return front;
	}

	glm::vec3 getRight() {
		return right;
	}

	glm::vec3 getUp() {
		return up;
	}

	glm::mat4 getModelMatrix() {
		glm::mat4 matrix = glm::mat4(1.0f);

		matrix = glm::translate(matrix, origin);
		matrix = glm::translate(matrix, position);
		matrix *= glm::mat4_cast(rotation);
		matrix = glm::scale(matrix, scale);

		return matrix;
	}

	// Behaviour
	void setBehaviour(std::shared_ptr<Behaviour> behaviour) { 
		this->behaviour = behaviour;
	}

	void start() {
		if (behaviour) {
			behaviour->start(*this);
		}
	}

	void update() {
		if (behaviour) {
			behaviour->update(*this);
		}
	}

	// Layers
	void addLayer(int ID) {
		layers.push_back(ID);
	}

	void removeLayer(int ID) {
		layers.erase(std::remove(layers.begin(), layers.end(), ID), layers.end());
	}

	bool checkLayer(int ID) {
		return (std::find(layers.begin(), layers.end(), ID) != layers.end());
	}

	// Appearance
	void setColour(glm::vec3 colour) {
		this->colour = colour;
	}

	void setColour(float red, float green, float blue) {
		colour = glm::vec3(red, green, blue);
	}

	glm::vec3 getColour() {
		return colour;
	}

	void setGrid(bool value) {
		grid = value;
	}

	bool getGrid() {
		return grid;
	}

protected:
	glm::vec3 position;
	glm::quat rotation;
	glm::vec3 scale;

	glm::vec3 origin;

	glm::vec3 front;
	glm::vec3 right;
	glm::vec3 up;

	glm::vec3 colour;
	bool grid;

	std::shared_ptr<Behaviour> behaviour;
	std::shared_ptr<Collider> collider;

	std::vector<int> layers;

	void updateDirectionVectors() {
		front = rotation * glm::vec3(0, 0, 1);
		right = rotation * glm::vec3(1, 0, 0);
		up =	rotation * glm::vec3(0, 1, 0);
	}
};