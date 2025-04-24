#include "oglrpch.h"
#include "Missile.h"

Missile::Missile(float speed, glm::vec3 position)
	: _speed(speed), _position(position),
	vertices
	{
		-0.10f, -0.5f, 0.0f, 0.0f, // 0
		0.10f, -0.5f, 1.0f, 0.0f, // 1
		0.0f,  0.25f, 0.5f, 1.0f, // 2
	},
	indices
	{
		0, 1, 2
	}
{
	transform.position = _position;
}

Missile::~Missile()
{

}

void Missile::MoveMissile(float dt)
{
	transform.position.y += _speed * dt;
}

glm::mat4& Missile::GetWorldMatrix()
{
	return transform.worldMatrix;
}

glm::vec3 Missile::GetPosition()
{
	return transform.position;
}

float* Missile::GetVertices()
{
	return vertices;
}

unsigned int* Missile::GetIndices()
{
	return indices;
}
