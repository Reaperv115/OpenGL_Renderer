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
	player.Init("src/Textures/other player.png");
}

void Level::Update(Timer timer)
{
	player.Update(timer);
}

void Level::Render()
{
	player.Render();
}
