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
	position = glm::vec3(0.0f, -2.3f, 0.0f);
	speed = 5.0f;
}

void Player::Update(Timer timer, double xpos, double ypos)
{
	std::cout << "XPos: " << xpos << '\n' <<
		"YPos: " << ypos;
}

void Player::Render()
{
	Renderer::DrawTriangle();
}

void Player::LoadAssets(const std::string& filepath)
{
	shipTexture = new Texture(filepath);
}
