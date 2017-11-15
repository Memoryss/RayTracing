#ifndef __CONTEXT_H__
#define __CONTEXT_H__

namespace RayTracing
{
    enum BufferType
    {
        BT_R8G8B8A8;    //RGBA ¹²32Î»
    };

    class Context
    {
    public:
        Context();
        ~Context();

        void 

    private:
        int m_width;
        int m_height;

        BufferType m_bufferType;
        void *m_buffer;     //äÖÈ¾µÄbuffer
    };
}

#endif