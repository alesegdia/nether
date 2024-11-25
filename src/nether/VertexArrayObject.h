#pragma once

#include "nether/GLType.h"

namespace nether
{

    class VertexArrayObject
    {
    public:
        void Generate()
        {
            glGenVertexArrays(1, &VAO);
            // aether::gl::check_error();
        }

        void AddVertexAttribPointer(unsigned int index, int size, GLType type, GLBoolean normalized, GLsizei stride, GLvoid* pointer)
        {
            glVertexAttribPointer(index, size, GLenum(type), GLboolean(normalized), stride, pointer);
        }

        void Bind()
        {
            glBindVertexArray(VAO);
        }

        void EnableVertexAttribArray(unsigned int index)
        {
            glEnableVertexAttribArray(index);
        }

        void Delete()
        {
            glDeleteVertexArrays(1, &VAO);
        }

        void Unbind()
        {
            glBindVertexArray(0);
        }

    private:
        unsigned int VAO;

    };

}
