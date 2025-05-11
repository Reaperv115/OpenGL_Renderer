#pragma once
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include <VertexArray.h>
#include <Texture.h>




class Renderer2D
{
public:
	void InitRenderer2D();
	void PrepareScene();
	void Draw();

	static void DrawQuad();
};