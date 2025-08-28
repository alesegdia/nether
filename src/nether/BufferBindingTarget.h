#pragma once

#include <nether/NetherGL.h>

namespace nether
{
    enum class BufferBindingTarget : GLenum
    {
        ArrayBuffer = GL_ARRAY_BUFFER,
        ElementArrayBuffer = GL_ELEMENT_ARRAY_BUFFER
    };

}