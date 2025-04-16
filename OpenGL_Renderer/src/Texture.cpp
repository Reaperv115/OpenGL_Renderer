#include "oglrpch.h"
#include "Texture.h"

Texture::Texture(const std::string& filepath)
	: _id(0), filePath(filepath), localBuffer(nullptr), width(0), height(0), bpP(0)
{
	stbi_set_flip_vertically_on_load(1);
	localBuffer = stbi_load(filepath.c_str(), &width, &height, &bpP, 4);

	Call(glGenTextures(1, &_id));
	Call(glBindTexture(GL_TEXTURE_2D, _id));

	Call(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	Call(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	Call(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	Call(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	Call(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, localBuffer));
	Call(glBindTexture(GL_TEXTURE_2D, 0));

	if (localBuffer)
		stbi_image_free(localBuffer);
}

Texture::Texture()
{

}

Texture::~Texture()
{
	Call(glDeleteTextures(1, &_id));
}

unsigned int Texture::LoadSkyBox(const std::vector<std::string> faces)
{
	Call(glGenTextures(1, &skyboxId));
	Call(glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxId));

	int width, height, numChannels;
	unsigned char* data;
	for (unsigned int i = 0; i < faces.size(); ++i)
	{
		unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &numChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
		}
		else
		{
			std::cout << "failed to load cubemap path: " << faces[i] << std::endl;
			stbi_image_free(data);
		}
	}

	Call(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	Call(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	Call(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	Call(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
	Call(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE));

	return skyboxId;
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
