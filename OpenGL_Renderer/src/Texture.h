#pragma once
#include "Renderer.h"
class Texture
{
private:
	unsigned int _id;
	unsigned int skyboxId;
	std::string filePath;
	unsigned char* localBuffer;
	int width, height, bpP;
public:
	Texture(const std::string& filepath);
	Texture();
	~Texture();


	void Bind(unsigned int slot = 0) const;
	void Unbind() const;
	void LoadTexture(const std::string& filepath);

	inline int GetWidth() const { return width; }
	inline int GetHeight() const { return height; }
};

