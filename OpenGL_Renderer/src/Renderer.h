#pragma once
#include <GL/glew.h>
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

// C++ macros for debugging opengl
#define ASSERT(x) if (!(x)) __debugbreak();
#define Call(x) GetErrors();\
	x;\
	ASSERT(LogCall(#x, __FILE__, __LINE__))
void GetErrors();

bool LogCall(const char* function, const char* file, int line);

class Renderer
{
public:
	void Clear() const;
	void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
	void Draw(const VertexArray& va, const VertexBuffer& vb, const Shader& shader) const;
};
