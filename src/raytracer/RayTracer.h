#ifndef __RAY_TRACER_H__
#define __RAY_TRACER_H__

#include <memory>
#include <vector>
#include <glm/vec4.hpp>

namespace RayTracing
{
    enum BufferType;
    
    class Ray;
    class Light;
    class Camera;
    class Scene;
    class Context;

    class RayTracer
    {
    public:
        RayTracer(std::shared_ptr<Context> ctx);
        ~RayTracer();

        void Clear();

        void Begin();

        void End();

        void Present(void *targetBuffer, BufferType type);

        void SetCamera(std::shared_ptr<Camera> camera);

        void SetScene(std::shared_ptr<Scene> scene);

        void SetLight(std::shared_ptr<Light> light);

        void RenderDepth(float maxDepth);

        void RenderNormal();

        void RenderNoReflect();

        void RenderReflect(int maxReflectLevel);

        glm::vec4 traceOnce(std::shared_ptr<Ray> ray, int &maxReflectLevel);

    protected:
        void WriteBuffer(int x, int y, const glm::vec4 &color);

    private:

        std::shared_ptr<Camera> m_camera;   //相机
		std::shared_ptr<Scene> m_scene;     //scene

        std::shared_ptr<Context> m_ctx;     //上下文

        std::shared_ptr<Light> m_light;     //场景灯光
    };
}

#endif