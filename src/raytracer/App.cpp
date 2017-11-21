#include "App.h"
#ifdef WIN32
#include <windows.h>
#else
#include <sys/time.h>
#endif

namespace RayTracing
{

    App::App()
    {

    }

    App::~App()
    {

    }

    void App::Init(int w, int h)
    {
        m_height = h;
        m_width = w;

        OnInit(w, h);
    }

    void App::Update()
    {
        static DWORD lastTick = getTickCount();
        DWORD currTick = getTickCount();

        PreUpdate();

        OnUpdate(m_frameTime);

        PostUpdate();

        m_frameTime = (currTick - lastTick) * 0.001f;
        lastTick = currTick;

//         float frameRate = 1.f / m_frameTime;
// 
//         std::stringstream wss;
//         wss << "ray tracing | frame rate:" << frameRate;
//         SetWindowText(m_hwnd, wss.str().c_str());
    }

    void App::Stop()
    {
        OnStop();
    }

    void App::Resize(int w, int h)
    {
        m_width = w;
        m_height = h;
        OnResize(w, h);
    }

    unsigned long App::getTickCount()
    {
#ifdef WIN32
        return GetTickCount();
#else
        struct timeval tv;
        gettimeofday(&tv, 0);
        return unsigned((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
#endif
    }

}