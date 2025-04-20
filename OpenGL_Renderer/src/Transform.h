#pragma once
#include "oglrpch.h"

struct Transform
{
	glm::vec3 position;
	glm::mat4 worldMatrix;
	glm::vec3 scale;
};