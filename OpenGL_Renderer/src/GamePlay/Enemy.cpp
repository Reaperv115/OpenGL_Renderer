#include "oglrpch.h"
#include "Enemy.h"

Enemy::Enemy(glm::vec3 position, float speed)
	: _position(position), _speed(speed),
	Vertices
	{
		-0.25f, -0.25f, 0.0f, 0.0f, // 0
		0.25f, -0.25f, 1.0f, 0.0f, // 1
		0.0f,  0.25f, 0.5f, 1.0f, // 2
	},
	Indices
   {
		0, 2, 1
   }
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

float* Enemy::GetVertices()
{
	return Vertices;
}

unsigned int* Enemy::GetIndices()
{
	return Indices;
}
