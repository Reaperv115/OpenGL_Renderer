#include "oglrpch.h"
#include "Player.h"

Player::Player(float speed, glm::vec3 position)
	: _speed(speed), _position(position),
	playerVertices
	{ -0.25f, -0.25f, 0.0f, 0.0f, // 0
		0.25f, -0.25f, 1.0f, 0.0f, // 1
		0.0f,  0.25f, 0.5f, 1.0f, // 2
	},
	playerIndices
   {
	0, 1, 2
   }
{
	transform.position = _position;
}
Player::Player()
{

}


Player::~Player()
{

}

glm::vec3 Player::GetPosition() const
{
	return transform.position;
}

glm::mat4& Player::GetworldMatrix()
{
	return transform.worldMatrix;
}

float Player::GetSpeed() const
{
	return _speed;
}


float* Player::GetPlayerVertices()
{
	return playerVertices;
}

unsigned int* Player::GetPlayerIndices()
{
	return playerIndices;
}

void Player::SetSpeed(float speed)
{
	_speed = speed;
}

void Player::MovePlayer(float dt)
{
	transform.position.x += _speed * dt;
}


