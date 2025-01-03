#pragma once

#include <memory>
#include <vector>
#include <algorithm>
#include <string>

#include "glm/glm.hpp"

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

private:
	static std::vector<Line> lines;
};