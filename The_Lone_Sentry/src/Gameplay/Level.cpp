#include "oglrpch.h"
#include "Level.h"

Level::Level()
{
	
}

Level::~Level()
{
	
}

void Level::Init()
{
	player.Init("src/Assets/Textures/other player.png");
	missile->Init("src/Assets/Textures/missile.png");
}

void Level::Update(Timer timer)
{
	player.Update(timer);
}

void Level::Render()
{
	player.Render();
}
