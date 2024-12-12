#pragma once

#include "Behaviour.h"

class CameraBehaviour : public Behaviour {
public:
	void start(Transform& transform) override;
	void update(Transform& transform) override;

private:
	const float slowSpeed = 0.4f;
	const float fastSpeed = 0.8f;
	const float sensitivity = 0.15f;
};