#pragma once
#include "Timer.h"
#include "../Graphics/Graphics.h"
#include "Camera/Camera.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"

class Renderer
{
public:
	Renderer(float width, float height, const std::string& windowname);
	void Clear();
	void BeginScene();

	std::shared_ptr<Graphics> GetGFX();
	static void DrawTriangle();
	static void DrawTriangle(glm::vec3 position, Texture* texture);

	static void DrawRectangle(glm::vec3 position, float rotation);
	static void DrawRectangle(glm::vec3 position);
private:
	std::shared_ptr<Graphics> gfx;
	void Init(float width, float height, const std::string& windowname);
	void InitializeGeometry();
	void PrepareGemoetry();
protected:
	Camera camera;

};


struct Square
{
	std::shared_ptr<VertexArray> va;
	std::shared_ptr<VertexBuffer> vb;
	std::shared_ptr<IndexBuffer> ib;
	std::shared_ptr<Shader> textureShader;
	std::shared_ptr<Shader> colorShader;
	std::shared_ptr<Texture> texture;
	std::shared_ptr<VertexBufferLayout> vbl;

	glm::vec3 color = glm::vec3(1.0f, 0.0f, 0.0f);

	Square(glm::vec3 _color)
		:color(_color)
	{
	}
	Square()
	{ }
}; static Square* square;

struct Triangle
{
	std::shared_ptr<VertexArray> va;
	std::shared_ptr<VertexBuffer> vb;
	std::shared_ptr<IndexBuffer> ib;
	std::shared_ptr<Shader> TextureShader;
	std::shared_ptr<Shader> colorShader;
	std::shared_ptr<Texture> texture;
	std::shared_ptr<VertexBufferLayout> vbl;

	glm::vec3 color = glm::vec3(0.0f, 0.0f, 1.0f);

	Triangle(glm::vec3 _position, glm::vec3 _color)
		:color(_color)
	{
	}
	Triangle()
	{

	}
}; static Triangle* triangle;