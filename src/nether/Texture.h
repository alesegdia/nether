#pragma once

#include "nether/TextureFormat.h"
#include "nether/TextureMinFilter.h"
#include "nether/TextureMagFilter.h"
#include "nether/TextureUnit.h"
#include "nether/TextureWrap.h"


#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <iostream>

namespace nether
{

    class Texture
    {
    public:



        int LoadFromFile(const char* filePath, TextureFormat format)
        {
            stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.

            int width, height, numChannels;
            m_data = stbi_load(filePath, &width, &height, &numChannels, 0);

            if (m_data != nullptr)
            {
                glGenTextures(1, &m_texture);
                glBindTexture(GL_TEXTURE_2D, m_texture);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, static_cast<GLint>(m_xWrap));
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, static_cast<GLint>(m_yWrap));
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, static_cast<GLint>(m_minFilter));
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, static_cast<GLint>(m_magFilter));

                switch (format)
                {
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
            else
            {
                std::cout << "Failed to load texture.";
                return -1;
            }

            return 0;
        }

        void Bind(nether::TextureUnit texUnit)
        {
            glActiveTexture(GLenum(texUnit));
            glBindTexture(GL_TEXTURE_2D, m_texture);
        }

        bool IsValid()
        {
            return m_data != nullptr;
        }

        void SetXWrap(TextureWrap xWrap)
        {
            m_xWrap = xWrap;
        }

        void SetYWrap(TextureWrap yWrap)
        {
            m_yWrap = yWrap;
        }

        void SetMinFilter(TextureMinFilter minFilter)
        {
            m_minFilter = minFilter;
        }

        void SetMagFilter(TextureMagFilter magFilter)
        {
            m_magFilter = magFilter;
        }

    private:
        TextureWrap m_xWrap = TextureWrap::Repeat;
        TextureWrap m_yWrap = TextureWrap::Repeat;

        TextureMinFilter m_minFilter = TextureMinFilter::Linear;
        TextureMagFilter m_magFilter = TextureMagFilter::Linear;

        unsigned char* m_data;
        unsigned int m_texture;

    };


}
