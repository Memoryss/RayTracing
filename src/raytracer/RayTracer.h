#ifndef __RAY_TRACER_H__
#define __RAY_TRACER_H__

#include <memory>
#include <glm/vec4.hpp>

namespace RayTracing
{
    enum BufferType;

    class Light;
    class Camera;
    class Node;
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

        void SetNode(std::shared_ptr<Node> node);

        void SetLight(std::shared_ptr<Light> light);

        void RenderDepth(float maxDepth);

        void RenderNormal();

        void RayTrace();

    protected:
        void WriteBuffer(int x, int y, const glm::vec4 &color);

    private:
        int m_width{};
        int m_height{};

        std::shared_ptr<Camera> m_camera;   //���
        std::shared_ptr<Node> m_node;       //��ʱ�Ȼ���һ��Node

        std::shared_ptr<Context> m_ctx;     //������

        std::shared_ptr<Light> m_light;     //�����ƹ�
    };
}

#endif