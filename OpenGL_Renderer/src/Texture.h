#pragma once
#include "ErrorLogging.h"


class Texture
{
private:
	std::string filePath;
	unsigned int _id;
	unsigned char* localBuffer;
	int width, height, bpP;
	std::vector<unsigned char*> localBuffers;
public:
	Texture(const std::string& filepath);
	Texture();
	~Texture();



	void Bind(unsigned int slot = 0) const;
	void Unbind() const;

	inline int GetWidth() const { return width; }
	inline int GetHeight() const { return height; }

};

