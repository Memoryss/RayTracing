#include "Context.h"
#include <iostream>
#include <assert.h>

namespace RayTracing
{

    Context::Context(int width, int height, BufferType type)
        : m_width(width), m_height(height), m_bufferType(type)
    {
        assert(width > 0 && height > 0);

        m_buffer = new u8[width * height * (int)type / 8];
    }

    Context::~Context()
    {
        if (m_buffer)
        {
            delete m_buffer;
            m_buffer = nullptr;
        }
    }

    void * Context::GetBuffer()
    {
        return m_buffer;
    }

    RayTracing::BufferType Context::GetBufferType() const
    {
        return m_bufferType;
    }

    void Context::Clear()
    {
        memset(m_buffer, 0, m_width * m_height * (int)m_bufferType / 8);
    }

    void Context::Present(void *targetBuffer, BufferType targetType)
    {
        int target_offset = (int)m_bufferType / 8;
        int src_offset = (int)targetType / 8;

        m_linePatch = m_width * (int)targetType / 8;
        m_linePatch = ((m_linePatch + 3) / 4) * 4;

        u8 *tData = (u8*)targetBuffer;
        u8 *sData = (u8*)m_buffer;
        switch (targetType)
        {
        case RayTracing::BT_B8G8R8:
            for (int i = 0; i < m_height; ++i)
            {
                for (int j = 0; j < m_width; ++j)
                {
                    for (int k = 0; k < src_offset; ++k)
                    {
                        tData[j * src_offset + k] = sData[j * target_offset + k];
                    }
                }

                tData += m_linePatch;
                sData += m_width * target_offset;
            }
            break;
        case RayTracing::BT_B8G8R8A8:
            memcpy(targetBuffer, m_buffer, sizeof(u8) * (int)BT_B8G8R8A8 / 8);
            break;
        default:
            break;
        }
    }

    int Context::GetWidth() const
    {
        return m_width;
    }

    int Context::GetHeight() const
    {
        return m_height;
    }
}