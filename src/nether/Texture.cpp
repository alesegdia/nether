#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "Texture.h"
#include <iostream>

namespace nether {

	int Texture::LoadFromFile(const std::string& filePath) {
		int numChannels;
		unsigned char* data = stbi_load(filePath.c_str(), &m_width, &m_height, &numChannels, 0);

		TextureFormat textureFormat = TextureFormat::RGB8;
		if(numChannels == 4)
		{
			textureFormat = TextureFormat::RGBA8;
		}
		else if(numChannels == 3)
		{
			textureFormat = TextureFormat::RGB8;
		}
		else
		{
			assert(false);
		}

		if (data != nullptr) {
			Create(m_width, m_height, data, textureFormat);
			stbi_image_free(data);
		}
		else {
			std::cout << "Failed to load texture.";
			return -1;
		}

		return 0;
	}

	void Texture::Create(int width, int height, unsigned char* pixels, TextureFormat format, bool createMipMaps)
	{
		nether::gl::genTextures(1, &m_texture);
		nether::gl::bindTexture(GL_TEXTURE_2D, m_texture);
		nether::gl::texParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, static_cast<GLint>(m_xWrap));
		nether::gl::texParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, static_cast<GLint>(m_yWrap));
		nether::gl::texParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, static_cast<GLint>(m_minFilter));
		nether::gl::texParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, static_cast<GLint>(m_magFilter));

		switch (format) {
		case TextureFormat::RGB8:
			std::cout << "RGB8 format not currently supported. Loading RGB8 format makes it crash for some reason." << std::endl;
			// nether::gl::texImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);
			return;
			break;
		case TextureFormat::RGBA8:
			nether::gl::texImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
			break;
		}

		if(createMipMaps)
		{
			nether::gl::generateMipmap(GL_TEXTURE_2D);
		}
	}

	void Texture::Bind(TextureUnit texUnit)
	{
		nether::gl::activeTexture(GLenum(texUnit));
		nether::gl::bindTexture(GL_TEXTURE_2D, m_texture);
	}

	void Texture::Bind()
	{
		nether::gl::bindTexture(GL_TEXTURE_2D, m_texture);
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