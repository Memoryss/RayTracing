#include "RayTracer.h"

#include "Node.h"
#include "Camera.h"
#include <glm/detail/func_geometric.hpp>

namespace RayTracing
{

    RayTracer::RayTracer()
    {

    }

    RayTracer::RayTracer(int width, int height) : m_height(height), m_width(width)
    {
    }

    RayTracer::~RayTracer()
    {

    }

    void RayTracer::SetCamera(std::shared_ptr<Camera> camera)
    {
        m_camera = camera;
    }

    void RayTracer::SetNode(std::shared_ptr<Node> node)
    {
        m_node = node;
    }

    void RayTracer::RenderDepth(float maxDepth)
    {
        for (int i = 0; i < m_height; ++i)
        {
            //屏幕上 向下为正y轴  与右手坐标系相反
            float ratioY = 1 - float(i) / m_height;
            for (int j = 0; j < m_width; ++j)
            {
                float ratioX = float(j) / m_width;
                auto ray = m_camera->ProductRay(ratioX, ratioY);
                auto result = m_node->Intersect(ray);
                if (result->node.get() != NULL)
                {
                    //把距离信息映射到深度上，用来显示 深度为0显示白色 深度越深  越黑
                    float depth = 255 - glm::min((float)(result->distance / maxDepth) * 255, 255.f);
                }
            }
        }
    }

}