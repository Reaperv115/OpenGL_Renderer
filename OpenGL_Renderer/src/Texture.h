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

	unsigned int LoadSkyBox(const std::vector<std::string> faces);

	void Bind(unsigned int slot = 0) const;
	void Unbind() const;

	unsigned int GetSkyBoxId() { return skyboxId; }

	inline int GetWidth() const { return width; }
	inline int GetHeight() const { return height; }
};

