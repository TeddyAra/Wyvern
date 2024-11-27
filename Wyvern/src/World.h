#pragma once

class World {
public:
	World();
	~World();

	float getDebug();
	void setDebug(float debug);

private:
	float debug;
};