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
	position = glm::vec2(0.0f, 0.0f);
	speed = 5.0f;
}

void Player::Update(Timer timer)
{
	glfwGetCursorPos(Graphics::GetContext()->GetWindow(), &xPos, &yPos);

	double newxPos = xPos - prevxPos;
	double newyPos = yPos - prevyPos;


	angle = atan2(newxPos, newyPos);
	rotation += angle;

	prevxPos = xPos;
	prevyPos = yPos;

	std::cout << "Angle: " << angle << std::endl;

}

void Player::Render()
{
	Renderer::DrawTriangle(position, glm::radians(rotation));
}

void Player::LoadAssets(const std::string& filepath)
{
	shipTexture = new Texture(filepath);
}
