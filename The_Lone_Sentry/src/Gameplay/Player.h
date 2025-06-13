#pragma once
#include "Renderer/Renderer.h"

class Player
{
public:
	Player(float speed);
	Player();
	~Player();

	void Init(const std::string& filepath);
	void Update(Timer timer);
	void Render();

	void LoadAssets(const std::string& filepath);

private:
	Texture* shipTexture;
	glm::vec3 position;
	glm::vec3 rotationVector;
	float centerX, centerY;
	float speed = 5.0f;
};
