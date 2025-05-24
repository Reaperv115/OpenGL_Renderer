#pragma once
#include "Player.h"

class Level
{
public:
	Level();
	~Level();

	void Init();
	void Update(Timer timer, double xpos, double ypos);
	void Render();

private:
	Player player;
};