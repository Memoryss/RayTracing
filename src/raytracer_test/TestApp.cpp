#include "TestApp.h"
#include "Context.h"
#include "RayTracer.h"
#include "Sphere.h"
#include "Camera.h"
#include "Light.h"
#include "Material.h"
#include "Scene.h"
#include "Plane.h"
#include <sstream>

namespace RayTracing
{

    TestApp::TestApp(HWND hwnd, int w, int h) : m_hwnd(hwnd)
    {

    }

    TestApp::~TestApp()
    {
        DeleteObject(m_offscreenBitmap);
        DeleteDC(m_offscreenDC);

        m_ctx.reset();
        m_rayTracer.reset();
    }

    void TestApp::OnMouseMove(int x, int y)
    {
        static int lastX = x;
        static int lastY = y;

        if (GetKeyState(VK_RBUTTON) & 0x80)
        {
            int deltaX = lastX - x;
            float scaleX = (float)deltaX / m_width;

            int deltaY = lastY - y;
            float scaleY = (float)deltaY / m_height;

            m_camera->OnMouseMove(scaleX, scaleY);
        }

        lastX = x;
        lastY = y;
    }

    void TestApp::PreUpdate()
    {
        m_rayTracer->Clear();
        m_rayTracer->Begin();
    }

    void TestApp::PostUpdate()
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

    void TestApp::OnInit(int w, int h)
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

		auto scene = std::make_shared<Scene>();

        auto simpleMaterial = std::make_shared<SimpleMaterial>(0.1f, 0.5f);
		auto plane = std::make_shared<Plane>(glm::vec3(0.f, 1.f, 0.f), 0.f);
		plane->SetMaterial(simpleMaterial);

		auto phongMaterial1 = std::make_shared<PhongMaterial>(glm::vec3(0.f, 0.f, 1.f), glm::vec3(1.f, 1.f, 1.f), 16.f, 0.25f);
        auto sphere1 = std::make_shared<Sphere>(glm::vec3(10, 10, -10), 10.f);
		sphere1->SetMaterial(phongMaterial1);

		auto phongMaterial2 = std::make_shared<PhongMaterial>(glm::vec3(1.f, 0.f, 0.f), glm::vec3(1.f, 1.f, 1.f), 16.f, 0.25f);
		auto sphere2 = std::make_shared<Sphere>(glm::vec3(-10, 10, -10), 10.f);
		sphere2->SetMaterial(phongMaterial2);

		scene->AddChild(plane);
		scene->AddChild(sphere1);
		scene->AddChild(sphere2);

        m_camera = std::make_shared<Camera>(glm::vec3(0, 5, 15), glm::vec3(0, 0, -1), glm::vec3(0, 1, 0), 90.f);
        m_light = std::make_shared<DirectionLight>();
        m_light->m_direction = glm::vec3(-1.f, -1.f, -1.f);
        
        m_rayTracer->SetCamera(m_camera);
        m_rayTracer->SetScene(scene);
        m_rayTracer->SetLight(m_light);
    }

    void TestApp::OnUpdate()
    {
        m_rayTracer->RenderReflect(3);
    }

    void TestApp::OnStop()
    {
        m_ctx.reset();
        m_rayTracer.reset();
        m_scene.reset();
        m_camera.reset();
    }

    void TestApp::OnResize(int w, int h)
    {
        DeleteObject(m_offscreenBitmap);
        DeleteDC(m_offscreenDC);

        OnInit(w, h);
        m_ctx->Resize(w, h);
    }

}