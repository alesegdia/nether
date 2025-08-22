#pragma once

#include "nethergl.h"

namespace nether
{
    enum class TextureWrap : GLint
    {
        Repeat = GL_REPEAT,
        MirroredRepeat = GL_MIRRORED_REPEAT,
        ClampToEdge = GL_CLAMP_TO_EDGE,
        ClampToBorder = GL_CLAMP_TO_BORDER,
    };
}
