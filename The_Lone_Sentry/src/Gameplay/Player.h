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
	glm::vec2 position;
	glm::mat4 rotationMatrix;
	float speed;
	float rotation;
	double xPos, yPos;
	double prevxPos, prevyPos;
	float angle;
};
