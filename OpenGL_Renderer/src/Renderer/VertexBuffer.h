#pragma once
class VertexBuffer
{
private:
	unsigned int vbId;
public:
	VertexBuffer(const void* data, unsigned int size);
	VertexBuffer();
	~VertexBuffer();

	void Bind() const ;
	void Unbind() const;

	void CreateBuffer(const void* data, unsigned int size);
};

