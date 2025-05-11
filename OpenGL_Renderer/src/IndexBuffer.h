#pragma once
class IndexBuffer
{
private:
	unsigned int ibId;
	unsigned int _count;
public:
	IndexBuffer(const unsigned int* data, const unsigned int count);
	IndexBuffer();
	~IndexBuffer();

	void Bind() const ;
	void Unbind() const;

	void CreateBuffer(const unsigned int* data, const unsigned int count);

	inline unsigned int GetCount() const { return _count; }
};

