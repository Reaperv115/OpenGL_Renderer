#include "oglrpch.h"
#include "Player.h"

Player::Player()
{

}

Player::Player(float speed)
	: _speed(speed)
{
}

Player::~Player()
{

}

void Player::Init(const std::string& filepath)
{
	LoadAssets(filepath);
}

void Player::Update(Timer timer)
{
	std::cout << timer.GetSeconds() << std::endl;
}

void Player::LoadAssets(const std::string& filepath)
{
	shipTexture = Texture2D::CreateTexture(filepath);
}
