#pragma once


namespace nether
{
    enum class TextureFormat
    {
		// Color formats
		RGB8,           // 8-bit RGB
		RGBA8,          // 8-bit RGBA
		RGB16F,         // 16-bit float RGB (HDR)
		RGBA16F,        // 16-bit float RGBA (HDR)
		RGB32F,         // 32-bit float RGB (HDR)
		RGBA32F,        // 32-bit float RGBA (HDR)
		R8,             // Single channel 8-bit
		RG8,            // Two channel 8-bit

		// Depth formats
		Depth16,        // 16-bit depth
		Depth24,        // 24-bit depth
		Depth32F,       // 32-bit float depth

		// Stencil formats
		Stencil8,       // 8-bit stencil

		// Combined formats
		Depth24Stencil8 // 24-bit depth + 8-bit stencil
    };

	class TextureFormatUtils
	{
	public:
		static unsigned int GetGLInternalFormat(TextureFormat format)
		{
			switch(format)
			{
			case TextureFormat::RGB8: return GL_RGB8;
			case TextureFormat::RGBA8: return GL_RGBA8;
			case TextureFormat::RGB16F: return GL_RGB16F;
			case TextureFormat::RGBA16F: return GL_RGBA16F;
			case TextureFormat::RGB32F: return GL_RGB32F;
			case TextureFormat::RGBA32F: return GL_RGBA32F;
			case TextureFormat::R8: return GL_R8;
			case TextureFormat::RG8: return GL_RG8;
			case TextureFormat::Depth16: return GL_DEPTH_COMPONENT16;
			case TextureFormat::Depth24: return GL_DEPTH_COMPONENT24;
			case TextureFormat::Depth32F: return GL_DEPTH_COMPONENT32F;
			case TextureFormat::Stencil8: return GL_STENCIL_INDEX8;
			case TextureFormat::Depth24Stencil8: return GL_DEPTH24_STENCIL8;
			default: return GL_RGBA8;
			}
		}

		static unsigned int GetGLFormat(TextureFormat format)
		{
			switch(format)
			{
			case TextureFormat::RGB8:
			case TextureFormat::RGB16F:
			case TextureFormat::RGB32F:
				return GL_RGB;
			case TextureFormat::RGBA8:
			case TextureFormat::RGBA16F:
			case TextureFormat::RGBA32F:
				return GL_RGBA;
			case TextureFormat::R8:
				return GL_RED;
			case TextureFormat::RG8:
				return GL_RG;
			case TextureFormat::Depth16:
			case TextureFormat::Depth24:
			case TextureFormat::Depth32F:
				return GL_DEPTH_COMPONENT;
			case TextureFormat::Stencil8:
				return GL_STENCIL_INDEX;
			case TextureFormat::Depth24Stencil8:
				return GL_DEPTH_STENCIL;
			default:
				return GL_RGBA;
			}
		}

		static unsigned int GetGLType(TextureFormat format)
		{
			switch(format)
			{
			case TextureFormat::RGB8:
			case TextureFormat::RGBA8:
			case TextureFormat::R8:
			case TextureFormat::RG8:
				return GL_UNSIGNED_BYTE;
			case TextureFormat::RGB16F:
			case TextureFormat::RGBA16F:
				return GL_HALF_FLOAT;
			case TextureFormat::RGB32F:
			case TextureFormat::RGBA32F:
			case TextureFormat::Depth32F:
				return GL_FLOAT;
			case TextureFormat::Depth16:
				return GL_UNSIGNED_SHORT;
			case TextureFormat::Depth24:
				return GL_UNSIGNED_INT;
			case TextureFormat::Stencil8:
				return GL_UNSIGNED_BYTE;
			case TextureFormat::Depth24Stencil8:
				return GL_UNSIGNED_INT_24_8;
			default:
				return GL_UNSIGNED_BYTE;
			}
		}

		static bool IsDepthFormat(TextureFormat format)
		{
			return format == TextureFormat::Depth16 ||
				   format == TextureFormat::Depth24 ||
				   format == TextureFormat::Depth32F ||
				  format == TextureFormat::Depth24Stencil8;
		}

		static bool IsStencilFormat(TextureFormat format)
		{
			return format == TextureFormat::Stencil8 ||
				   format == TextureFormat::Depth24Stencil8;
		}

	};

}
