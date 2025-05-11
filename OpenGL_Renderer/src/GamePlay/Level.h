#pragma once
#include "Player.h"

class Level
{
public:
	Level();
	~Level();

	void Update(Timer timer);

private:
	Player player;
};