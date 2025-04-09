#include "oglrpch.h"
#include "IndexBuffer.h"
#include "Renderer.h"

IndexBuffer::IndexBuffer(const unsigned int* data, const unsigned int count)
	: _count(count)
{
	Call(glGenBuffers(1, &ibId));
	Call(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibId));
	Call(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer()
{
	Call(glDeleteBuffers(1, &ibId));
}

void IndexBuffer::Bind() const
{
	Call(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibId));
}

void IndexBuffer::Unbind() const
{
	Call(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
