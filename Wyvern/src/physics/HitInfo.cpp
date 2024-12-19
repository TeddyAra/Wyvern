#include "HitInfo.h"

HitInfo::HitInfo()
	: object(nullptr), hitPoint(glm::vec3(0.0f, 0.0f, 0.0f)), normal(glm::vec3(0.0f, 0.0f, 0.0f)), distance(0.0f)
{

}

HitInfo::~HitInfo() {

}