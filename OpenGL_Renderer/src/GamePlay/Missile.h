#pragma once
#include "Transform.h"
class Missile
{
public:
	Missile(float speed, glm::vec3 position);
	Missile(float speed);
	~Missile();

	void MoveMissile(float dt);
	glm::mat4& GetWorldMatrix();
	glm::vec3 GetPosition();
private:
	Transform transform;
	float _speed;
};

