#include "Context.h"
#include "common.h"

namespace RayTracing
{

    Context::Context(int width, int height, BufferType bufferType, void *buffer)
        : m_width(width), m_height(height), m_bufferType(bufferType), m_buffer(buffer)
    {

    }

    Context::~Context()
    {

    }

    void * Context::GetBuffer()
    {
        return m_buffer;
    }

    BufferType Context::GetBufferType()
    {
        return m_bufferType;
    }

    int Context::GetWidth()
    {
        return m_width;
    }

    int Context::GetHeight()
    {
        return m_height;
    }
}