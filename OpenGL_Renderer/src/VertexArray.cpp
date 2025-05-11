#include "oglrpch.h"
#include "VertexArray.h"
#include "Renderer/Renderer.h"
#include "VertexBufferLayout.h"

VertexArray::VertexArray()
{
	Call(glGenVertexArrays(1, &id));
}

VertexArray::~VertexArray()
{
	Call(glDeleteVertexArrays(1, &id));
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	Bind();
	vb.Bind();
	const auto& elements = layout.GetElements();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < elements.size(); i++)
	{
		const auto& element = elements[i];
		Call(glEnableVertexAttribArray(i));
		Call(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)offset));
		offset += element.count * VertexBufferElements::GetSizeOfType(element.type);
	}
}

void VertexArray::AddBuffer(const IndexBuffer& ib)
{
	Bind();
	ib.Bind();
}

void VertexArray::Bind() const
{
	Call(glBindVertexArray(id));
}

void VertexArray::Unbind() const
{
	Call(glBindVertexArray(0));
}

