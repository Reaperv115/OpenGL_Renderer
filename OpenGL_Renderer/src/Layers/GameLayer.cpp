#include "oglrpch.h"
#include "GameLayer.h"

GameLayer::GameLayer()
{

}

void GameLayer::OnAttach()
{
	level = new Level();
}

void GameLayer::OnDetach()
{
}

void GameLayer::InitGameLayer()
{
	
}

void GameLayer::OnUpdate(Timer timer)
{
	level->Update(timer);
}

void GameLayer::Draw()
{

}
