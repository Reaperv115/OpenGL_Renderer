#pragma once
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "VertexBufferLayout.h"
#include "Texture.h"
#include "../Graphics/Graphics.h"
#include "Camera.h"
#include "Shader.h"
#include "Transform.h"
#include "Shapes.h"
#include "GamePlay/Player.h"




class Renderer
{
public:
	Renderer(float width, float height, const std::string& windowname);
	void Clear();
	void PrepareScene();
	void Update(float dt);
	void Draw();
	std::shared_ptr<Graphics> GetGFX();
private:
	std::shared_ptr<Graphics> gfx;
	void Init(float width, float height, const std::string& windowname);
	void DrawQuad();
	Player player;
protected:
	Camera camera;
	std::shared_ptr<VertexArray> vertexArray;
	std::shared_ptr<VertexBuffer> vertexBuffer;
	std::shared_ptr<VertexBufferLayout> vbl;
	std::shared_ptr<IndexBuffer> indexBuffer;
	glm::mat4 mvp;

};
