#pragma once

#include "nether/GLType.h"

namespace nether
{

    class VertexArrayObject
    {
    public:
		VertexArrayObject() : VAO(0) {}

        void Generate()
        {
            nether::gl::genVertexArrays(1, &VAO);
            // aether::gl::check_error();
        }

        void AddVertexAttribPointer(unsigned int index, int size, GLType type, GLBoolean normalized, GLsizei stride, GLvoid* pointer)
        {
            nether::gl::vertexAttribPointer(index, size, GLenum(type), GLboolean(normalized), stride, pointer);
        }

        void Bind()
        {
            nether::gl::bindVertexArray(VAO);
        }

        void EnableVertexAttribArray(unsigned int index)
        {
            nether::gl::enableVertexAttribArray(index);
        }

        void Delete()
        {
            nether::gl::deleteVertexArrays(1, &VAO);
        }

        void Unbind()
        {
            nether::gl::bindVertexArray(0);
        }

    private:
        unsigned int VAO;

    };

}
