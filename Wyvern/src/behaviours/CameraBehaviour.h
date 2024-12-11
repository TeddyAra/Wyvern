#pragma once

#include "Behaviour.h"

class CameraBehaviour : public Behaviour {
public:
	void start(Transform& transform) override;
	void update(Transform& transform) override;

private:
	const float slowSpeed = 1.0f;
	const float fastSpeed = 2.0f;
	const float sensitivity = 0.25f;
};