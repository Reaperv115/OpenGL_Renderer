#pragma once
#include <vector>
#include <GL/glew.h>
#include "Renderer.h"

struct VertexBufferElements
{
	unsigned int type;
	unsigned int count;
	unsigned char normalized;

	static unsigned int GetSizeOfType(unsigned int type)
	{
		switch (type)
		{
			case GL_FLOAT:			return 4;
			case GL_UNSIGNED_INT:	return 4;
			case GL_UNSIGNED_BYTE:	return 1;
		}
		ASSERT(false);
		return 0;
	}
};

class VertexBufferLayout
{
private:
	std::vector<VertexBufferElements> _elements;
	unsigned int _stride;
public:
	VertexBufferLayout()
		: _stride(0){};

	template<typename T>
	void Push(int count)
	{
		static_assert(false);
	}

	template<>
	void Push<float>(int count)
	{
		VertexBufferElements vbe;
		vbe.count = count;
		vbe.type = GL_FLOAT;
		vbe.normalized = GL_FALSE;
		_elements.push_back(vbe);
		_stride += count * VertexBufferElements::GetSizeOfType(GL_FLOAT);
	}
	template<>
	void Push<unsigned int>(int count)
	{
		VertexBufferElements vbe;
		vbe.count = count;
		vbe.type = GL_UNSIGNED_INT;
		vbe.normalized = GL_FALSE;
		_elements.push_back(vbe);
		_stride += count * VertexBufferElements::GetSizeOfType(GL_UNSIGNED_INT);
	}
	template<>
	void Push<unsigned char>(int count)
	{
		VertexBufferElements vbe;
		vbe.count = count;
		vbe.type = GL_UNSIGNED_BYTE;
		vbe.normalized = GL_TRUE;
		_elements.push_back(vbe);
		_stride += count * VertexBufferElements::GetSizeOfType(GL_UNSIGNED_BYTE);
	}

	inline const std::vector<VertexBufferElements> GetElements() const { return _elements; }
	inline unsigned int GetStride() const { return _stride; }
};