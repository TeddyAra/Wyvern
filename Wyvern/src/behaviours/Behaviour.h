#pragma once

#include "Input.h"

class Transform;

class Behaviour {
public:
	Behaviour() {}
	virtual ~Behaviour() = default;

	virtual void start(Transform& transform) = 0;
	virtual void update(Transform& transform) = 0;
};