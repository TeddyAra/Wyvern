#include "Debug.h"

std::vector<Line> Debug::lines;

void Debug::addLine(glm::vec3 posA, glm::vec3 posB, glm::vec4 colour) {
	Line line(posA, posB, colour);
	lines.push_back(line);
}

void Debug::clearLines() {
	lines.clear();
}

std::vector<Line>& Debug::getLines() {
	return lines;
}