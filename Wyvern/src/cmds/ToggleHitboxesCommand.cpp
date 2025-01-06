#include "ToggleHitboxesCommand.h"

#include <iostream>

#include "InteractionController.h"

#include "Debug.h"

ToggleHitboxesCommand::ToggleHitboxesCommand(std::shared_ptr<InteractionController> controller)
	: ICommand(controller)
{

}

void ToggleHitboxesCommand::execute() {
	if (args.size() == 0) {
		std::cerr << "No arguments given to toggle hitbox command" << std::endl;
		return;
	}

	bool cast = false;
	bool toggle = false;
	for (std::any arg : args) {
		if (arg.type() == typeid(bool)) {
			toggle = std::any_cast<bool>(arg);
			cast = true;
			break;
		}
	}

	if (!cast) {
		std::cerr << "Wrong argument(s) given to toggle hitbox command" << std::endl;
		return;
	}

	Debug::setDrawHitboxes(toggle);

	/*if (toggle) {
		std::vector<std::shared_ptr<Transform>>& objects = controller->getObjects();
		std::vector<std::shared_ptr<Transform>>& transformTools = controller->getTransformTools();
		objects.insert(objects.end(), transformTools.begin(), transformTools.end());
	
		for (const std::shared_ptr<Transform>& object : objects) {
			if (!object->getCollider()) continue;

			std::vector<glm::vec3> vertices = object->getCollider()->getVertices();
			std::vector<unsigned int> indices = object->getCollider()->getIndices();

			glm::mat4 matrix = object->getModelMatrix();

			for (int i = 0; i < indices.size(); i += 3) {
				glm::vec2 triangleBaryPosition;
				float triangleDistance;

				glm::vec3 pos1 = glm::vec3(matrix * glm::vec4(vertices[indices[i]], 1.0f));
				glm::vec3 pos2 = glm::vec3(matrix * glm::vec4(vertices[indices[i + 1]], 1.0f));
				glm::vec3 pos3 = glm::vec3(matrix * glm::vec4(vertices[indices[i + 2]], 1.0f));
			
				Debug::addLine(pos1, pos2, glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
				Debug::addLine(pos2, pos3, glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
				Debug::addLine(pos3, pos1, glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
			}
		}
	} else {
		Debug::clearLines();
	}*/
}