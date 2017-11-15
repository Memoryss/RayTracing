#ifndef __CONTEXT_H__
#define __CONTEXT_H__

#include <memory>

namespace RayTracing
{
    enum BufferType
    {
        BT_R8G8B8A8,    //RGBA 共32位
    };

    class Context
    {
    public:
        Context(int width, int height, BufferType bufferType, void *buffer);
        ~Context();

        void *GetBuffer();
        BufferType GetBufferType();

        int GetWidth();
        int GetHeight();

    private:
        int m_width;
        int m_height;

        BufferType m_bufferType;    //buffer类型
        void *m_buffer;             //渲染的buffer
    };
}

#endif