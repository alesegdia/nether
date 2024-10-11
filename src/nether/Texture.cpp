#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "Texture.h"
#include <iostream>
#include <glad/gl.h> // Ensure you include the necessary OpenGL headers

namespace nether {

	int Texture::LoadFromFile(const std::string& filePath, TextureFormat format) {
		int width, height, numChannels;
		m_data = stbi_load(filePath.c_str(), &width, &height, &numChannels, 0);

		if (m_data != nullptr) {
			glGenTextures(1, &m_texture);
			glBindTexture(GL_TEXTURE_2D, m_texture);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, static_cast<GLint>(m_xWrap));
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, static_cast<GLint>(m_yWrap));
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, static_cast<GLint>(m_minFilter));
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, static_cast<GLint>(m_magFilter));

			switch (format) {
			case TextureFormat::RGB8:
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, m_data);
				break;
			case TextureFormat::RGBA8:
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_data);
				break;
			}
			glGenerateMipmap(GL_TEXTURE_2D);
			stbi_image_free(m_data);
		}
		else {
			std::cout << "Failed to load texture.";
			return -1;
		}

		return 0;
	}

	void Texture::Bind(TextureUnit texUnit) {
		glActiveTexture(GLenum(texUnit));
		glBindTexture(GL_TEXTURE_2D, m_texture);
	}

	bool Texture::IsValid() {
		return m_data != nullptr;
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