#include "oglrpch.h"
#include "Level.h"

Level::Level()
{
	player.Init("src/Textures/other player.png");
}

Level::~Level()
{

}

void Level::Update(Timer timer)
{
	player.Update(timer);
}
