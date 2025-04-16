#pragma once
#include "transform.h"

class Enemy
{
public:
	Enemy(glm::vec3 position, float speed);
	~Enemy();

	void MoveEnemy(float dt);
	glm::vec3 GetPosition() const;
private:
	Transform transform;
	glm::vec3 _position;
	float _speed;
};

