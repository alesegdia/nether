#pragma once

#include <glad/gl.h>

namespace nether
{
    enum class TextureMagFilter : GLint
    {
        Nearest = GL_NEAREST,
        Linear = GL_LINEAR,
    };

}
