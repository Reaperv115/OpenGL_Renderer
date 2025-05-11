#pragma once
#include "Shapes.h"
#include "Platform/Textures/Texture2D.h"

class Player
{
public:
	Player(float speed);
	Player();
	~Player();

	void Init(const std::string& filepath);
	void Update(Timer timer);

	void LoadAssets(const std::string& filepath);

private:
	glm::vec2 position;
	float _speed;
	Texture* shipTexture;
};
