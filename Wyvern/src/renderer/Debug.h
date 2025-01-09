#pragma once

#include "Renderer.h"

#include <memory>
#include <vector>
#include <algorithm>
#include <string>

#include "Transform.h"

struct Line {
	glm::vec3 posA;
	glm::vec3 posB;
	glm::vec4 colour;

	Line(glm::vec3 posA, glm::vec3 posB, glm::vec4 colour) {
		this->posA = posA;
		this->posB = posB;
		this->colour = colour;
	}
};

class Debug {
public:
	Debug() = delete;

	static void addLine(glm::vec3 posA, glm::vec3 posB, glm::vec4 colour = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
	static void clearLines();
	static std::vector<Line>& getLines();
	static void addObject(std::shared_ptr<Transform> object);
	static void setDrawHitboxes(bool value);
	static void drawHitboxes(GLuint colourLoc);
	static void drawCircle(glm::vec3 pos, glm::vec3 normal, float radius, float steps, glm::vec4 colour, GLuint colourLoc);

private:
	static std::vector<Line> lines;
	static std::vector<std::shared_ptr<Transform>> objects;
	static bool hitboxToggle;
};