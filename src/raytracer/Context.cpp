#include "Context.h"
#include <iostream>
#include <assert.h>

namespace RayTracing
{

    Context::Context(int width, int height, BufferType type)
        : m_bufferType(type)
    {
        init(width, height);
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

    void Context::Resize(int w, int h)
    {
        if (m_buffer != nullptr)
        {
            delete m_buffer;
            m_buffer = nullptr;
        }

        init(w, h);
    }

    void Context::init(int w, int h)
    {
        assert(w > 0 && h > 0);
        m_width = w;
        m_height = h;
        m_buffer = new u8[w * h * (int)m_bufferType / 8];
    }

}