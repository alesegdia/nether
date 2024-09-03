#pragma once

#include <glad/gl.h>

namespace nether
{
    enum class GLType : GLuint
    {
        Float = GL_FLOAT,
        Int = GL_INT,
        Bool = GL_BOOL
    };

    enum class GLBoolean : GLboolean
    {
        True = GL_TRUE,
        False = GL_FALSE
    };

}