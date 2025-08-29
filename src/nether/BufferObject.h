#pragma once

#include <vector>

#include "nether/BufferBindingTarget.h"
#include "nether/BufferUsage.h"
#include "nether/NetherGL.h"


namespace nether
{
    class BufferObject
    {
    public:
        void Generate(BufferBindingTarget pBufferBindingTarget, BufferUsage pBufferUsage = BufferUsage::StaticDraw)
        {
            SetBufferBindingTarget(pBufferBindingTarget);
            SetBufferUsage(pBufferUsage);
            nether::gl::genBuffers(1, &vbo);
        }

        template <typename T>
        void UploadBufferData(const std::vector<T>& items)
        {
            nether::gl::bufferData(static_cast<GLenum>(bufferBindingTarget), sizeof(T) * items.size(), items.data(), GLenum(bufferUsage));
        }

        void Bind()
        {
            nether::gl::bindBuffer(static_cast<GLenum>(bufferBindingTarget), vbo);
        }

        void Unbind()
        {
            nether::gl::bindBuffer(static_cast<GLenum>(bufferBindingTarget), 0);
        }

        void Delete()
        {
            nether::gl::deleteBuffers(1, &vbo);
        }

    private:
        void SetBufferUsage(BufferUsage pBufferUsage)
        {
            bufferUsage = pBufferUsage;
        }

        void SetBufferBindingTarget(BufferBindingTarget pBufferBindingTarget)
        {
            bufferBindingTarget = pBufferBindingTarget;
        }


        BufferUsage bufferUsage = BufferUsage::StaticDraw;
        BufferBindingTarget bufferBindingTarget = BufferBindingTarget::ArrayBuffer;
        unsigned int vbo = 0;

    };

}