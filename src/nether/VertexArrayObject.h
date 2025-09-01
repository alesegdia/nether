#pragma once

#include "nether/GLType.h"

#ifdef NETHER_GL_ERROR_CHECKING
#include <iostream>
#endif

#ifdef AETHER_USE_QT
#include <QOpenGLContext>
#endif

namespace nether
{

    class VertexArrayObject
    {
    public:
		VertexArrayObject() : VAO(0)
		{}

        void Generate()
        {
            
            nether::gl::genVertexArrays(1, &VAO);
            
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
             VAO = 0;
        }

        void Unbind()
        {
            nether::gl::bindVertexArray(0);
        }

        bool IsValid() const
        {
            return VAO != 0;
        }

        unsigned int GetVAO() const
        {
            return VAO;
        }


    private:
        unsigned int VAO;
    };

}
