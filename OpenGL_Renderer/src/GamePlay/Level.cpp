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

void Level::Update(Timer timer, double xpos, double ypos)
{
	player.Update(timer, xpos, ypos);
}

void Level::Render()
{
	player.Render();
}
