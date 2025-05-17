#pragma once
#include "Timer.h"
#include "../Graphics/Graphics.h"
#include "Camera/Camera.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Textures/Texture.h"
#include "Transform.h"

class Renderer
{
public:
	Renderer(float width, float height, const std::string& windowname);
	void Clear();
	void PrepareScene();
	void Update(Timer timer);
	std::shared_ptr<Graphics> GetGFX();

	static void DrawTriangle();
private:
	std::shared_ptr<Graphics> gfx;
	void Init(float width, float height, const std::string& windowname);
	void InitializeGeometry();
	void PrepareGemoetry();
protected:
	Camera camera;
	glm::mat4 mvp;

};


struct Square
{
	std::shared_ptr<VertexArray> va;
	std::shared_ptr<VertexBuffer> vb;
	std::shared_ptr<IndexBuffer> ib;
	std::shared_ptr<Shader> shader;
	std::shared_ptr<Texture> texture;
	std::shared_ptr<VertexBufferLayout> vbl;
	Transform transform;

	glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);
}; static Square square;

struct Triangle
{
	std::shared_ptr<VertexArray> va;
	std::shared_ptr<VertexBuffer> vb;
	std::shared_ptr<IndexBuffer> ib;
	std::shared_ptr<Shader> shader;
	std::shared_ptr<Texture> texture;
	std::shared_ptr<VertexBufferLayout> vbl;
	Transform transform;

	glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);
}; static Triangle triangle;