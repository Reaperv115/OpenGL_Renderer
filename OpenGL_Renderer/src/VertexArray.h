#pragma once
#include "VertexBuffer.h"
#include "IndexBuffer.h"
class VertexBufferLayout;

class VertexArray
{
private:
	unsigned int id;
public:
	VertexArray();
	~VertexArray();

	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
	void AddBuffer(const IndexBuffer& ib);

	void Bind() const;
	void Unbind() const;
};

