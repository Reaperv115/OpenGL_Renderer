#include "oglrpch.h"
#include "Missile.h"

Missile::Missile(float speed, glm::vec3 position)
	: _speed(speed)
{
	transform.position = position;
}

Missile::Missile(float speed)
	: _speed(speed)
{

}

Missile::~Missile()
{

}

void Missile::MoveMissile(float dt)
{
	transform.position.y -= _speed * dt;
}

glm::mat4& Missile::GetWorldMatrix()
{
	return transform.worldMatrix;
}

glm::vec3 Missile::GetPosition()
{
	return transform.position;
}
