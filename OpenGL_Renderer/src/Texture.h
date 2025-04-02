#pragma once
#include "Renderer.h"
class Texture
{
private:
	unsigned int _id;
	std::string filePath;
	unsigned char* localBuffer;
	int width, height, bpP;
public:
	Texture(const std::string& filepath);
	~Texture();

	void Bind(unsigned int slot = 0) const;
	void Unbind() const;

	inline int GetWidth() const { return width; }
	inline int GetHeight() const { return height; }
};

