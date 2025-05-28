#pragma once
#include "Renderer/Renderer.h"

class Player
{
public:
	Player(float speed);
	Player();
	~Player();

	void Init(const std::string& filepath);
	void Update(Timer timer, double xpos, double ypos);
	void Render();

	void LoadAssets(const std::string& filepath);

private:
	Texture* shipTexture;

	glm::vec2 position;
	float speed;
};
