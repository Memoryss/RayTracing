#ifndef __DEPTH_APP_H__
#define __DEPTH_APP_H__

#include "App.h"
#include <windows.h>
#include <memory>

namespace RayTracing
{
    class RayTracer;
    class Scene;
    class Camera;
    class DirectionLight;

    class DepthApp : public App
    {
    public:
        DepthApp(HWND hwnd, int w, int h);
        ~DepthApp();

    protected:

        virtual void PreUpdate() override;

        virtual void PostUpdate() override;

        virtual void OnInit(int w, int h) override;


        virtual void OnUpdate() override;


        virtual void OnStop() override;

    private:
        HWND m_hwnd;
        HDC m_offscreenDC;
        HBITMAP m_offscreenBitmap;

        std::shared_ptr<RayTracer> m_rayTracer;
        std::shared_ptr<Scene> m_scene;
        std::shared_ptr<Camera> m_camera;
        std::shared_ptr<DirectionLight> m_light;
    };
}

#endif