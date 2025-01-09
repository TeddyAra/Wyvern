#include "Debug.h"

#include "World.h"

std::vector<Line> Debug::lines;
std::vector<std::shared_ptr<Transform>> Debug::objects;
bool Debug::hitboxToggle;

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

void Debug::addObject(std::shared_ptr<Transform> object) {
	objects.push_back(object);
}

void Debug::setDrawHitboxes(bool value) {
	hitboxToggle = value;
}

void Debug::drawHitboxes(GLuint colourLoc) {
	glDisable(GL_DEPTH_TEST);

	glLineWidth(2.0f);
	for (const Line& line : Debug::getLines()) {
		glUniform4f(colourLoc, line.colour.r, line.colour.g, line.colour.b, line.colour.a);

		glBegin(GL_LINES);
		glVertex3f(line.posA.x, line.posA.y, line.posA.z);
		glVertex3f(line.posB.x, line.posB.y, line.posB.z);
		glEnd();
	}

	if (hitboxToggle) {

		glUniform4f(colourLoc, 0.75f, 0.0f, 0.1f, 1.0f);

		for (const std::shared_ptr<Transform>& object : objects) {
			if (!object->getCollider()) continue;

			std::vector<glm::vec3> vertices = object->getCollider()->getVertices();
			std::vector<unsigned int> indices = object->getCollider()->getIndices();

			glm::mat4 matrix = object->getModelMatrix();

			for (int i = 0; i < vertices.size(); i++) {
				vertices[i] = glm::vec3(matrix * glm::vec4(vertices[i], 1.0f));
			}

			for (int i = 0; i < indices.size(); i += 3) {
				glm::vec3 pos1 = vertices[indices[i]];
				glm::vec3 pos2 = vertices[indices[i + 1]];
				glm::vec3 pos3 = vertices[indices[i + 2]];

				glBegin(GL_LINES);
				glVertex3f(pos1.x, pos1.y, pos1.z);
				glVertex3f(pos2.x, pos2.y, pos2.z);
				glVertex3f(pos2.x, pos2.y, pos2.z);
				glVertex3f(pos3.x, pos3.y, pos3.z);
				glVertex3f(pos3.x, pos3.y, pos3.z);
				glVertex3f(pos1.x, pos1.y, pos1.z);
				glEnd();
			}
		}
	}

	glEnable(GL_DEPTH_TEST);
	glLineWidth(4.0f);
	glUniform4f(colourLoc, 0.3f, 0.5f, 0.8f, 1.0f);

	for (const std::shared_ptr<Transform>& object : World::getWorld()->getSelected()) {
		if (!object->getCollider()) continue;

		std::vector<glm::vec3> vertices = object->getCollider()->getVertices();
		std::vector<unsigned int> indices = object->getCollider()->getIndices();

		glm::mat4 matrix = object->getModelMatrix();

		for (int i = 0; i < vertices.size(); i++) {
			vertices[i] = glm::vec3(matrix * glm::vec4(vertices[i], 1.0f));
		}

		glm::vec3 pos1 = vertices[0];
		glm::vec3 pos2 = vertices[1];
		glm::vec3 pos3 = vertices[2];
		glm::vec3 pos4 = vertices[3];
		glm::vec3 pos5 = vertices[4];
		glm::vec3 pos6 = vertices[5];
		glm::vec3 pos7 = vertices[6];
		glm::vec3 pos8 = vertices[7];

		glBegin(GL_LINES);
		glVertex3f(pos1.x, pos1.y, pos1.z);
		glVertex3f(pos2.x, pos2.y, pos2.z);
		glVertex3f(pos2.x, pos2.y, pos2.z);
		glVertex3f(pos6.x, pos6.y, pos6.z);
		glVertex3f(pos6.x, pos6.y, pos6.z);
		glVertex3f(pos5.x, pos5.y, pos5.z);
		glVertex3f(pos5.x, pos5.y, pos5.z);
		glVertex3f(pos1.x, pos1.y, pos1.z);

		glVertex3f(pos3.x, pos3.y, pos3.z);
		glVertex3f(pos4.x, pos4.y, pos4.z);
		glVertex3f(pos4.x, pos4.y, pos4.z);
		glVertex3f(pos8.x, pos8.y, pos8.z);
		glVertex3f(pos8.x, pos8.y, pos8.z);
		glVertex3f(pos7.x, pos7.y, pos7.z);
		glVertex3f(pos7.x, pos7.y, pos7.z);
		glVertex3f(pos3.x, pos3.y, pos3.z);

		glVertex3f(pos1.x, pos1.y, pos1.z);
		glVertex3f(pos3.x, pos3.y, pos3.z);
		glVertex3f(pos2.x, pos2.y, pos2.z);
		glVertex3f(pos4.x, pos4.y, pos4.z);
		glVertex3f(pos5.x, pos5.y, pos5.z);
		glVertex3f(pos7.x, pos7.y, pos7.z);
		glVertex3f(pos6.x, pos6.y, pos6.z);
		glVertex3f(pos8.x, pos8.y, pos8.z);
		glEnd();
	}
}

void Debug::drawCircle(glm::vec3 pos, glm::vec3 normal, float radius, float steps, glm::vec4 colour, GLuint colourLoc) {
	glm::vec3 tangent = glm::cross(normal, glm::vec3(0.0f, 1.0f, 0.0f));
	if (glm::length(tangent) < 0.0001f) {
		tangent = glm::cross(normal, glm::vec3(1.0f, 0.0f, 0.0f));
	}
	tangent = glm::normalize(tangent);
	glm::vec3 biTangent = glm::normalize(glm::cross(normal, tangent));

	glLineWidth(4.0f);
	glUniform4f(colourLoc, colour.r, colour.g, colour.b, colour.a);

	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < steps; i++) {
		float angle = 2.0f * glm::pi<float>() * i / steps;
		glm::vec3 point = pos + radius * (cos(angle) * tangent + sin(angle) * biTangent);
		glVertex3f(point.x, point.y, point.z);
	}
	glEnd();
}