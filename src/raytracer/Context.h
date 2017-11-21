#ifndef __CONTEXT_H__
#define __CONTEXT_H__

#include <memory>
#include "common.h"

namespace RayTracing
{
    class Context
    {
    public:
        Context(int width, int height, BufferType type);
        ~Context();

        void *GetBuffer();
        BufferType GetBufferType() const;

        void Clear();

        void Present(void *targetBuffer, BufferType targetType);

        int GetWidth() const;
        int GetHeight() const;

        void Resize(int w, int h);

    protected:
        void init(int w, int h);

    private:
        int m_width{};
        int m_height{};
        int m_linePatch{};

        BufferType m_bufferType;
        void *m_buffer{nullptr};             //äÖÈ¾µÄbuffer
    };
}

#endif