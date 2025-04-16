#include "oglrpch.h"
#include "Player.h"

Player::Player(float speed, glm::vec3 position)
	: _speed(speed), _position(position)
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

float Player::GetSpeed() const
{
	return _speed;
}


void Player::SetSpeed(float speed)
{
	_speed = speed;
}

void Player::MovePlayer(float dt)
{
	transform.position.x += _speed * dt;
}
