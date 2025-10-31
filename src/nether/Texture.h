#pragma once

#include "nether/TextureFormat.h"
#include "nether/TextureMinFilter.h"
#include "nether/TextureMagFilter.h"
#include "nether/TextureUnit.h"
#include "nether/TextureWrap.h"

#include <string>

namespace nether {

	struct TextureDesc {
		int width;
		int height;
		unsigned char* pixels;
		TextureFormat format;
	};

	class Texture {
	public:
		int LoadFromFile(const std::string& filePath);
		void Create(int width, int height, unsigned char* pixels, TextureFormat format, bool createMipMaps);
		void Create(int width, int height, TextureFormat textureFormat, bool createMipMaps);
		void Bind(TextureUnit texUnit);
		void Bind();
		void SetXWrap(TextureWrap xWrap);
		void SetYWrap(TextureWrap yWrap);
		void SetMinFilter(TextureMinFilter minFilter);
		void SetMagFilter(TextureMagFilter magFilter);

		int GetWidth(int mipmapLevel = 0)
		{
			nether::gl::bindTexture(GL_TEXTURE_2D, m_texture);
			int w;
			nether::gl::getTexLevelParameteriv(GL_TEXTURE_2D, mipmapLevel, GL_TEXTURE_WIDTH, &w);
			return w;
		}

		int GetHeight(int mipmapLevel = 0)
		{
			nether::gl::bindTexture(GL_TEXTURE_2D, m_texture);
			int h;
			nether::gl::getTexLevelParameteriv(GL_TEXTURE_2D, mipmapLevel, GL_TEXTURE_HEIGHT, &h);
			return h;
		}

		int GetCachedWidth()
		{
			return m_width;
		}

		int GetCachedHeight()
		{
			return m_height;
		}

	private:
		TextureWrap m_xWrap = TextureWrap::Repeat;
		TextureWrap m_yWrap = TextureWrap::Repeat;
		TextureMinFilter m_minFilter = TextureMinFilter::Nearest;
		TextureMagFilter m_magFilter = TextureMagFilter::Nearest;
		int m_width = 0;
		int m_height = 0;
		unsigned int m_texture = 0;
	};

}