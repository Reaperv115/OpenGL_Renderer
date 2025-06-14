#pragma once
#include "../Renderer/Texture.h"
#include "../Renderer/Renderer.h"

class Missile
{
public:
	Missile(const std::string& filepath, glm::vec3 position);
	~Missile();

	void Init(const std::string& filepath);
	void OnUpdate(Timer timer);
	void Render();
private:
	void LoadAssets(const std::string& filepath);
private:
	float speed;
	glm::vec3 position;
	Texture* missileTexture;
};

