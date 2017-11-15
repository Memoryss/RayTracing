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
            //��Ļ�� ����Ϊ��y��  ����������ϵ�෴
            float ratioY = 1 - float(i) / m_height;
            for (int j = 0; j < m_width; ++j)
            {
                float ratioX = float(j) / m_width;
                auto ray = m_camera->ProductRay(ratioX, ratioY);
                auto result = m_node->Intersect(ray);
                if (result->node.get() != NULL)
                {
                    //�Ѿ�����Ϣӳ�䵽����ϣ�������ʾ ���Ϊ0��ʾ��ɫ ���Խ��  Խ��
                    float depth = 255 - glm::min((float)(result->distance / maxDepth) * 255, 255.f);
                }
            }
        }
    }

}