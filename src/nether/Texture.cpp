#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "Texture.h"
#include <iostream>

namespace nether {

	int Texture::LoadFromFile(const std::string& filePath, TextureFormat format) {
		int width, height, numChannels;
		unsigned char* data = stbi_load(filePath.c_str(), &width, &height, &numChannels, 0);

		if (data != nullptr) {
			Create(width, height, data, format);
			stbi_image_free(data);
		}
		else {
			std::cout << "Failed to load texture.";
			return -1;
		}

		return 0;
	}

	void Texture::Create(int width, int height, unsigned char* pixels, TextureFormat format)
	{
		glGenTextures(1, &m_texture);
		glBindTexture(GL_TEXTURE_2D, m_texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, static_cast<GLint>(m_xWrap));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, static_cast<GLint>(m_yWrap));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, static_cast<GLint>(m_minFilter));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, static_cast<GLint>(m_magFilter));

		switch (format) {
		case TextureFormat::RGB8:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);
			break;
		case TextureFormat::RGBA8:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
			break;
		}
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	void Texture::Bind(TextureUnit texUnit) {
		glActiveTexture(GLenum(texUnit));
		glBindTexture(GL_TEXTURE_2D, m_texture);
	}

	void Texture::SetXWrap(TextureWrap xWrap) {
		m_xWrap = xWrap;
	}

	void Texture::SetYWrap(TextureWrap yWrap) {
		m_yWrap = yWrap;
	}

	void Texture::SetMinFilter(TextureMinFilter minFilter) {
		m_minFilter = minFilter;
	}

	void Texture::SetMagFilter(TextureMagFilter magFilter) {
		m_magFilter = magFilter;
	}

}