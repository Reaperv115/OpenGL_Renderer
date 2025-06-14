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
	if (GetAsyncKeyState('A'))
		position.x -= speed * timer.GetDeltatime();
	if (GetAsyncKeyState('D'))
		position.x += speed * timer.GetDeltatime();

	if (position.x <= -2.5f)
		position.x = -2.5f;
	if (position.x > 2.5f)
		position.x = 2.5f;

	if (missiles.size() == 0)
	{ }
	else
	{
		for (Missile* missile : missiles)
		{
			missile->OnUpdate(timer);
		}
	}


	if (GetAsyncKeyState(VK_LBUTTON))
	{
		std::cout << "firing weapon" << std::endl;
		missiles.push_back(new Missile("src/Assets/Textures/missile.png", position));
	}

}

void Player::Render()
{
	Renderer::DrawTriangle(position, shipTexture);
	if (missiles.size() == 0)
	{
	}
	else
	{
		for (Missile* missile : missiles)
		{
			missile->Render();
		}
	}
}

void Player::LoadAssets(const std::string& filepath)
{
	shipTexture = new Texture(filepath);
}
