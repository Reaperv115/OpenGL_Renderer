#include "oglrpch.h"
#include "Player.h"

Player::Player()
{

}

Player::Player(float speed)
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
}

void Player::Render()
{
	Renderer::DrawTriangle();
}

void Player::LoadAssets(const std::string& filepath)
{
	shipTexture = new Texture(filepath);
}
