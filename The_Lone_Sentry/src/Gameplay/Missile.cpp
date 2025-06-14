#include "oglrpch.h"
#include "Missile.h"

Missile::Missile(const std::string& filepath, glm::vec3 position)
	:speed(5.0f)
{
	LoadAssets(filepath);
	this->position = position;
}

Missile::~Missile()
{

}

void Missile::Init(const std::string& filepath)
{
	
}

void Missile::OnUpdate(Timer timer)
{
	position.y += speed * timer.GetDeltatime();
}

void Missile::Render()
{
	Renderer::DrawTriangle(position, missileTexture);
}

void Missile::LoadAssets(const std::string& filepath)
{
	missileTexture = new Texture(filepath);
}
