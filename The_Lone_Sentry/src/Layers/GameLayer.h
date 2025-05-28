#pragma once
#include "Layer.h"
#include "GamePlay/Level.h"
#include "../Graphics/Graphics.h"

class GameLayer : public Layer
{
public:
	GameLayer();

	void OnAttach() override;
	void OnDetach() override;
	void OnUpdate(Timer timer) override;

	void InitGameLayer();

private:
	Level* level;
};

