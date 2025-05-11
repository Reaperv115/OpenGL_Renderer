#pragma once
#include "ErrorLogging.h"
#include "Texture.h"

class Texture2D : public Texture
{
public:
	Texture2D(const std::string& filepath);

	static Texture2D* CreateTexture(const std::string& filepath);
private:
	std::string path;
	int width, height;
	unsigned int _id;
};


