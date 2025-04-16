#include "oglrpch.h"
#include "Enemy.h"

Enemy::Enemy(glm::vec3 position, float speed)
	: _position(position), _speed(speed)
{
	transform.position = _position;
	transform.rotation = glm::vec3(1.0f);
}

Enemy::~Enemy()
{

}

void Enemy::MoveEnemy(float dt)
{
	_position.x -= _speed * dt;
}

glm::vec3 Enemy::GetPosition() const
{
	return transform.position;
}
