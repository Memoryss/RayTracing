#include "App.h"
#include <sstream>

namespace RayTracing
{

    App::App()
    {

    }

    App::~App()
    {

    }

    void App::Init(HWND hwnd, int w, int h) : m_hwnd(hwnd), m_height(h), m_width(w)
    {
        OnInit(w, h);
    }

    void App::Update()
    {
        static DWORD lastTick = GetTickCount();
        DWORD currTick = GetTickCount();

        PreUpdate();

        OnUpdate();

        PostUpdate();

        m_frameTime = (currTick - lastTick) * 0.001;
        lastTick = currTick;

        float frameRate = 1.f / m_frameTime;

        std::stringstream wss;
        wss << "ray tracing | frame rate:" << frameRate;
        SetWindowText(m_hwnd, wss.str().c_str());
    }

    void App::Stop()
    {
        OnStop();
    }
}