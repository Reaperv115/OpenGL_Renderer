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

glm::mat4& Player::GetworldMatrix()
{
	return transform.worldMatrix;
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

Missile* Player::FireMissile(float speed, glm::vec3 position)
{
	return new Missile(speed, position);
}
