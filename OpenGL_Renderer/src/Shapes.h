#pragma once
#include <VertexArray.h>
#include <Texture.h>
#include <Shader.h>
#include <Transform.h>

struct Square
{
	VertexArray* va;
	Texture* texture;
	Shader* shader;
	Transform transform;
}; static Square* square;