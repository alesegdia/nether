#pragma once

#include "nether/Color.h"

#include <glad/gl.h>


namespace nether
{

    class Renderer
    {
    public:

        void SetRendererClearColor(Color color)
        {
            clearColor = color;
        }

        void BeginRender()
        {
            glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
            glClear(clearBitField);
        }

        void SetColorBufferBit(bool set)
        {
            colorBufferBit = set;
            SetClearBits();
        }

        void SetDepthBufferBit(bool set)
        {
            glEnable(GL_DEPTH_TEST);
            depthBufferBit = set;
            SetClearBits();
        }

        /*
        void SetAccumBufferBit(bool set)
        {
            accumBufferBit = set;
        }
        */

        void SetStencilBufferBit(bool set)
        {
            stencilBufferBit = set;
            SetClearBits();
        }

        void SetWireframeMode()
        {
            mode = GL_LINE;
            UpdatePolygonMode();
        }

        void SetFillMode()
        {
            mode = GL_FILL;
            UpdatePolygonMode();
        }

        void SetFrontBack()
        {
            face = GL_FRONT_AND_BACK;
            UpdatePolygonMode();
        }

        void SetBack()
        {
            face = GL_BACK;
            UpdatePolygonMode();
        }

        void SetFront()
        {
            face = GL_FRONT;
            UpdatePolygonMode();
        }


    private:
        void UpdatePolygonMode()
        {
            glPolygonMode(face, mode);
        }

        void SetClearBits()
        {
            clearBitField = 0;
            SetBit(colorBufferBit, GL_COLOR_BUFFER_BIT);
            SetBit(depthBufferBit, GL_DEPTH_BUFFER_BIT);
            // SetBit(accumBufferBit, GL_ACCUM_BUFFER_BIT);
            SetBit(stencilBufferBit, GL_STENCIL_BUFFER_BIT);
        }

        void SetBit(bool set, GLbitfield bitField)
        {
            if (set)
            {
                clearBitField |= bitField;
            }
        }

        Color clearColor;
        GLbitfield clearBitField;
        bool colorBufferBit = false;
        bool depthBufferBit = false;
        // bool accumBufferBit = false;
        bool stencilBufferBit = false;

        GLenum face = GL_FRONT_AND_BACK;
        GLenum mode = GL_FILL;

    };

}
