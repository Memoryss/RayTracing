#ifndef __APP_H__
#define __APP_H__

namespace RayTracing
{
    class App
    {
    public:
        App();
        ~App();

        virtual void Init(int w, int h);

        virtual void OnInit(int w, int h) = 0;

        virtual void Update();

        virtual void Stop();

        virtual void PreUpdate() {}

        virtual void OnUpdate() = 0;

        virtual void PostUpdate() {}

        virtual void OnStop() = 0;

    protected:

        int m_width{};
        int m_height{};

        int m_frameTime;
    };

}

#endif
