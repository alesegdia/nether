#pragma once

#include "nether/TextureFormat.h"
#include "nether/TextureMinFilter.h"
#include "nether/TextureMagFilter.h"
#include "nether/TextureUnit.h"
#include "nether/TextureWrap.h"

#include <string>

namespace nether {

	class Texture {
	public:
		int LoadFromFile(const std::string& filePath, TextureFormat format);
		void Bind(TextureUnit texUnit);
		bool IsValid();
		void SetXWrap(TextureWrap xWrap);
		void SetYWrap(TextureWrap yWrap);
		void SetMinFilter(TextureMinFilter minFilter);
		void SetMagFilter(TextureMagFilter magFilter);

	private:
		TextureWrap m_xWrap = TextureWrap::Repeat;
		TextureWrap m_yWrap = TextureWrap::Repeat;
		TextureMinFilter m_minFilter = TextureMinFilter::Linear;
		TextureMagFilter m_magFilter = TextureMagFilter::Linear;
		unsigned char* m_data = nullptr;
		unsigned int m_texture = 0;
	};

}