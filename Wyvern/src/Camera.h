#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Camera {
public:
	Camera(float fov);
	~Camera();

	glm::vec3 getPosition();

	void setPosition(float x, float y, float z);
	void setPosition(glm::vec3 position);

	void translate(float x, float y, float z);
	void translate(glm::vec3 translation);

	glm::vec3 getRotation();

	void setRotation(float x, float y, float z);
	void setRotation(glm::vec3 rotation);

	void setYaw(float yaw);
	void setPitch(float pitch);

	void rotate(float x, float y, float z);
	void rotate(glm::vec3 rotation);

	void updateTransform();

	glm::mat4 getViewMatrix();

	void setFov(float fov);
	float getFov();

	glm::vec3 getFront();
	glm::vec3 getRight();
	glm::vec3 getUp();

private:
	glm::vec3 position;
	glm::vec3 rotation;

	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;

	float fov;
};