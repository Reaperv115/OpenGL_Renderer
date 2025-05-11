#pragma once
#include "Layer.h"
#include "GamePlay/Level.h"

class GameLayer : public Layer
{
public:
	GameLayer();

	void OnAttach() override;
	void OnDetach() override;
	void OnUpdate(Timer timer) override;

	void InitGameLayer();
	void Draw();

private:
	Level* level;
};

