#include "oglrpch.h"
#include "Enemy.h"

Enemy::Enemy(glm::vec3 position, float speed)
	: _position(position), _speed(speed)
{
	transform.position = _position;
	
}


Enemy::~Enemy()
{

}

void Enemy::MoveEnemy(float dt)
{
	if (transform.position.x >= 2.5f || transform.position.x <= -2.5f)
		_speed *= -1;
		
	if (!isStopped)
		transform.position.x += _speed * dt;
}

void Enemy::SetModelMatrix(glm::mat4& matrix)
{
	transform.worldMatrix = matrix;
}

void Enemy::StopTriangle(bool stopped)
{
	isStopped = stopped;
}

bool Enemy::IsStopped()
{
	return isStopped;
}

glm::vec3 Enemy::GetPosition() const
{
	return transform.position;
}

glm::mat4& Enemy::GetRotation()
{
	return transform.worldMatrix;
}
