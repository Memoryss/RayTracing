#ifndef __APP_H__
#define __APP_H__

#include <memory>

namespace RayTracing
{
    enum BufferType;
    class Context;

    class App
    {
    public:
        App();
        ~App();

        virtual void Init(int w, int h);

        virtual void Update();

        virtual void Stop();

        virtual void Resize(int w, int h);

        virtual void OnMouseMove(int x, int y) {}

        virtual void OnKeyDown(unsigned int key) {}

        virtual void OnKeyRelease(unsigned int key) {}

    protected:

        virtual void OnInit(int w, int h) = 0;

        virtual void PreUpdate() {}

        virtual void OnUpdate(float frame) = 0;

        virtual void PostUpdate() {}

        virtual void OnStop() = 0;

        virtual void OnResize(int w, int h) = 0;

    protected:
        unsigned long getTickCount();

    protected:

        int m_width{};
        int m_height{};

        float m_frameTime;

        BufferType m_bufferType;
        void *m_buffer{ nullptr };

        std::shared_ptr<Context> m_ctx;
    };

}

#endif
