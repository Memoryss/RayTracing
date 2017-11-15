#ifndef __RAY_TRACER_H__
#define __RAY_TRACER_H__

#include <memory>
#include <glm/vec4.hpp>

namespace RayTracing
{
    class Camera;
    class Node;
    class Context;

    class RayTracer
    {
    public:
        RayTracer(std::shared_ptr<Context> ctx);
        ~RayTracer();

        void SetCamera(std::shared_ptr<Camera> camera);

        void SetNode(std::shared_ptr<Node> node);

        void RenderDepth(float maxDepth);

    protected:
        void WriteBuffer(int x, int y, const glm::vec4 &color);

    private:
        int m_width{};
        int m_height{};

        std::shared_ptr<Camera> m_camera;   //���
        std::shared_ptr<Node> m_node;       //��ʱ�Ȼ���һ��Node

        std::shared_ptr<Context> m_ctx;     //������
    };
}

#endif