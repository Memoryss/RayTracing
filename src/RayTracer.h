#ifndef __RAY_TRACER_H__
#define __RAY_TRACER_H__

#include <memory>

namespace RayTracing
{
    class Camera;

    class RayTracer
    {
    public:
        RayTracer();
        RayTracer(int width, int height);
        ~RayTracer();

        void SetCamera(std::shared_ptr<Camera> camera);

        void SetNode(std::shared_ptr<Node> node);

        void RenderDepth(float maxDepth);

    private:
        int m_width{};
        int m_height{};

        std::shared_ptr<Camera> m_camera;   //���
        std::shared_ptr<Node> m_node;       //��ʱ�Ȼ���һ��Node
    };
}

#endif