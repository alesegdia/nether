#pragma once

#include <nether/NetherGL.h>

namespace nether
{
    enum class BufferUsage : GLenum
    {
        StaticDraw = GL_STATIC_DRAW,    // the data is set only once and used by the GPU at most a few times
        StreamDraw = GL_STREAM_DRAW,    // the data is set only once and used many times
        DynamicDraw = GL_DYNAMIC_DRAW   // the data is changed a lot and used many times
    };
}

