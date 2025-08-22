#pragma once

#include <vector>

#include "nether/BufferBindingTarget.h"
#include "nether/BufferUsage.h"


namespace nether
{
    class BufferObject
    {
    public:
        void Generate(BufferBindingTarget pBufferBindingTarget, BufferUsage pBufferUsage = BufferUsage::StaticDraw)
        {
            SetBufferBindingTarget(pBufferBindingTarget);
            SetBufferUsage(pBufferUsage);
            glGenBuffers(1, &vbo);
        }

        template <typename T>
        void UploadBufferData(const std::vector<T>& items)
        {
            glBufferData(static_cast<GLenum>(bufferBindingTarget), sizeof(T) * items.size(), items.data(), GLenum(bufferUsage));
        }

        void Bind()
        {
            glBindBuffer(static_cast<GLenum>(bufferBindingTarget), vbo);
        }

        void Unbind()
        {
            glBindBuffer(static_cast<GLenum>(bufferBindingTarget), 0);
        }

        void Delete()
        {
            glDeleteBuffers(1, &vbo);
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