#include "oglrpch.h"
#include "GameLayer.h"

GameLayer::GameLayer()
{

}

void GameLayer::OnAttach()
{
	level = new Level();
	level->Init();
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

	level->Render();
}
