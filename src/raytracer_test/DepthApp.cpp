#include "DepthApp.h"
#include "Context.h"
#include "RayTracer.h"
#include "Sphere.h"
#include "Camera.h"
#include <sstream>

namespace RayTracing
{

    DepthApp::DepthApp(HWND hwnd, int w, int h) : m_hwnd(hwnd)
    {

    }

    DepthApp::~DepthApp()
    {
        DeleteObject(m_offscreenBitmap);
        DeleteDC(m_offscreenDC);

        m_ctx.reset();
        m_rayTracer.reset();
    }

    void DepthApp::PreUpdate()
    {
        m_rayTracer->Clear();
        m_rayTracer->Begin();
    }

    void DepthApp::PostUpdate()
    {
        float frameRate = 1.f / m_frameTime;
        std::stringstream ss;
        ss << "ray tracing | frame rate:" << frameRate;
        SetWindowText(m_hwnd, ss.str().c_str());

        m_rayTracer->Present(m_buffer, m_bufferType);

        HDC hdc = GetDC(m_hwnd);
        BitBlt(hdc, 0, 0, m_width, m_height, m_offscreenDC, 0, 0, SRCCOPY);
        ReleaseDC(m_hwnd, hdc);

        m_rayTracer->End();
    }

    void DepthApp::OnInit(int w, int h)
    {
        HDC hdc = GetDC(m_hwnd);
        m_offscreenDC = CreateCompatibleDC(hdc);

        BITMAPINFO bi;
        memset(&bi, 0, sizeof(BITMAPINFO));
        bi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        bi.bmiHeader.biWidth = w;
        bi.bmiHeader.biHeight = -h;
        bi.bmiHeader.biPlanes = 1;
        bi.bmiHeader.biBitCount = 24;
        bi.bmiHeader.biCompression = BI_RGB;
        m_offscreenBitmap = CreateDIBSection(hdc, &bi, DIB_RGB_COLORS, (void **)&m_buffer, NULL, 0);
        m_bufferType = BT_B8G8R8;

        SelectObject(m_offscreenDC, m_offscreenBitmap);

        ReleaseDC(m_hwnd, hdc);

        m_ctx = std::make_shared<Context>(w, h, BT_B8G8R8A8);
        m_rayTracer = std::make_shared<RayTracer>(m_ctx);

        m_sphere = std::make_shared<Sphere>(glm::vec3(0, 10, -10), 10.f);
        m_camera = std::make_shared<Camera>(glm::vec3(0, 10, 10), glm::vec3(0, 0, -1), glm::vec3(0, 1, 0), 90.f);

        m_rayTracer->SetCamera(m_camera);
        m_rayTracer->SetNode(m_sphere);
    }

    void DepthApp::OnUpdate()
    {
        m_rayTracer->RenderDepth(20);
    }

    void DepthApp::OnStop()
    {
        m_ctx.reset();
        m_rayTracer.reset();
        m_sphere.reset();
        m_camera.reset();
    }
}