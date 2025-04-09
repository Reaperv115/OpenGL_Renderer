#include "oglrpch.h"
#include "VertexBuffer.h"
#include "Renderer.h"


VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
	Call(glGenBuffers(1, &vbId));
	Call(glBindBuffer(GL_ARRAY_BUFFER, vbId));
	Call(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer()
{
	Call(glDeleteBuffers(1, &vbId))
}

void VertexBuffer::Bind() const
{
	Call(glBindBuffer(GL_ARRAY_BUFFER, vbId));
}

void VertexBuffer::Unbind() const
{
	Call(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
