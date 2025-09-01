#pragma once

#include "nether/GLType.h"

#ifdef NETHER_GL_ERROR_CHECKING
#include <iostream>
#endif

namespace nether
{

    class VertexArrayObject
    {
    public:
		VertexArrayObject() : VAO(0) {}

        void Generate()
        {
            // Delete existing VAO if it exists to prevent resource leaks
            if (VAO != 0)
            {
                #ifdef NETHER_GL_ERROR_CHECKING
                std::cerr << "[NETHER VAO DEBUG] Deleting existing VAO " << VAO << " before generating new one" << std::endl;
                #endif
                Delete();
            }
            
            nether::gl::genVertexArrays(1, &VAO);
            
            #ifdef NETHER_GL_ERROR_CHECKING
            std::cerr << "[NETHER VAO DEBUG] Generated new VAO " << VAO << std::endl;
            #endif
            // aether::gl::check_error();
        }

        void AddVertexAttribPointer(unsigned int index, int size, GLType type, GLBoolean normalized, GLsizei stride, GLvoid* pointer)
        {
            nether::gl::vertexAttribPointer(index, size, GLenum(type), GLboolean(normalized), stride, pointer);
        }

        void Bind()
        {
            // Only bind if VAO has been generated (non-zero)
            if (VAO != 0)
            {
                #ifdef NETHER_GL_ERROR_CHECKING
                std::cerr << "[NETHER VAO DEBUG] Binding VAO " << VAO << std::endl;
                #endif
                nether::gl::bindVertexArray(VAO);
            }
            else
            {
                // This would cause GL_INVALID_OPERATION - help with debugging
                #ifdef NETHER_GL_ERROR_CHECKING
                std::cerr << "[NETHER VAO ERROR] Attempting to bind VAO that hasn't been generated (VAO = 0)" << std::endl;
                #endif
            }
        }

        void EnableVertexAttribArray(unsigned int index)
        {
            nether::gl::enableVertexAttribArray(index);
        }

        void Delete()
        {
            if (VAO != 0)
            {
                #ifdef NETHER_GL_ERROR_CHECKING
                std::cerr << "[NETHER VAO DEBUG] Deleting VAO " << VAO << std::endl;
                #endif
                nether::gl::deleteVertexArrays(1, &VAO);
                VAO = 0; // Reset to indicate it's no longer valid
            }
        }

        void Unbind()
        {
            #ifdef NETHER_GL_ERROR_CHECKING
            std::cerr << "[NETHER VAO DEBUG] Unbinding VAO (binding VAO 0)" << std::endl;
            #endif
            nether::gl::bindVertexArray(0);
        }

        // Add a method to check if VAO is valid
        bool IsValid() const
        {
            return VAO != 0;
        }

        // Add getter for debugging purposes
        unsigned int GetVAO() const
        {
            return VAO;
        }

    private:
        unsigned int VAO;

    };

}
