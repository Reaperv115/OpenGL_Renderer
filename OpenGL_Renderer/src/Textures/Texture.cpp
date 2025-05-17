#include "oglrpch.h"
#include "Texture.h"

Texture::Texture(const std::string& filepath)
	: filePath(filepath)
{
	int width, height, channels;
	stbi_set_flip_vertically_on_load(1);
	stbi_uc* data = stbi_load(filepath.c_str(), &width, &height, &channels, 0);

	GLenum internalFormat = 0, dataFormat = 0;
	if (channels == 4)
	{
		internalFormat = GL_RGBA8;
		dataFormat = GL_RGBA;
	}
	else if (channels == 3)
	{
		internalFormat = GL_RGB8;
		dataFormat = GL_RGB;
	}



	glCreateTextures(GL_TEXTURE_2D, 1, &_id);
	glTextureStorage2D(_id, 1, internalFormat, width, height);

	glTextureParameteri(_id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTextureParameteri(_id, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTextureParameteri(_id, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTextureParameteri(_id, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTextureSubImage2D(_id, 0, 0, 0, width, height, dataFormat, GL_UNSIGNED_BYTE, data);

	stbi_image_free(data);
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
