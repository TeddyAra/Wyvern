#include "BoxCollider.h"

BoxCollider::BoxCollider()
	: Collider()
{
	vertices = {
		{ -0.5f, -0.5f, -0.5f },
		{  0.5f, -0.5f, -0.5f },
		{ -0.5f,  0.5f, -0.5f },
		{  0.5f,  0.5f, -0.5f },
		{ -0.5f, -0.5f,  0.5f },
		{  0.5f, -0.5f,  0.5f },
		{ -0.5f,  0.5f,  0.5f },
		{  0.5f,  0.5f,  0.5f }
	};

	indices = {
		0, 2, 3,
		0, 3, 1,

		1, 3, 7,
		1, 7, 5,

		5, 7, 6,
		5, 6, 4,

		4, 6, 2,
		4, 2, 0,

		4, 0, 1,
		4, 1, 5,

		2, 6, 7,
		2, 7, 3
	};
}

BoxCollider::~BoxCollider() {

}

std::vector<glm::vec3> BoxCollider::getVertices() {
	return vertices;
}

std::vector<unsigned int> BoxCollider::getIndices() {
	return indices;
}