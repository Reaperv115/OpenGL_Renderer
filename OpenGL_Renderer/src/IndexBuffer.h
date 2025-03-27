#pragma once
class IndexBuffer
{
private:
	unsigned int ibId;
	unsigned int _count;
public:
	IndexBuffer(const unsigned int* data, const unsigned int count);
	~IndexBuffer();

	void Bind() const ;
	void Unbind() const;

	inline unsigned int GetCount() const { return _count; }
};

