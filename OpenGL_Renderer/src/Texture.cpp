#include "oglrpch.h"
#include "Texture.h"

Texture::Texture(const std::string& filepath)
	: filePath(filepath)
{
	
}

Texture::Texture()
{

}

Texture::~Texture()
{
	Call(glDeleteTextures(1, &_id));
}

void Texture::Bind(unsigned int slot /*= 0*/) const
{
	Call(glActiveTexture(GL_TEXTURE0 + slot));
	Call(glBindTexture(GL_TEXTURE_2D, _id));
}

void Texture::Unbind() const
{
	Call(glBindTexture(GL_TEXTURE_2D, 0));
}
