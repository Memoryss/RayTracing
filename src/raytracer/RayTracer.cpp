#include "RayTracer.h"

#include "Node.h"
#include "Camera.h"
#include <glm/detail/func_geometric.hpp>
#include "Context.h"

namespace RayTracing
{
    RayTracer::RayTracer(std::shared_ptr<Context> ctx)
    {
        assert(ctx.get() != nullptr);
        
        m_ctx = ctx;
        m_width = ctx->GetWidth();
        m_height = ctx->GetHeight();
    }

    RayTracer::~RayTracer()
    {
        m_ctx.reset();
        m_camera.reset();
        m_node.reset();
    }

    void RayTracer::Clear()
    {
        m_ctx->Clear();
    }

    void RayTracer::Begin()
    {

    }

    void RayTracer::End()
    {

    }

    void RayTracer::Present(void *targetBuffer, BufferType type)
    {
        m_ctx->Present(targetBuffer, type);
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
        assert(m_ctx.get() != nullptr || m_ctx->GetBuffer() != nullptr);
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
                    glm::vec4 color;
                    //把距离信息映射到深度上，用来显示 深度为0显示白色 深度越深  越黑
                    float depth = 255 - glm::min((float)(result->distance / maxDepth) * 255, 255.f);
                    color.r = depth;
                    color.g = depth;
                    color.b = depth;
                    color.a = 255;
                    WriteBuffer(j, i, color);
                }
            }
        }
    }

    void RayTracer::RenderNormal()
    {
        assert(m_ctx.get() != nullptr || m_ctx->GetBuffer() != nullptr);
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
                    glm::vec4 color;
                    //法线已经归一化 -1~1之间 映射到 0~255
                    color.r = (result->normal.x + 1) * 128;
                    color.g = (result->normal.y + 1) * 128;
                    color.b = (result->normal.z + 1) * 128;
                    color.a = 255;
                    WriteBuffer(j, i, color);
                }
            }
        }
    }

    void RayTracer::WriteBuffer(int x, int y, const glm::vec4 &color)
    {
        int index = 0;
        u8 *data = nullptr;
        switch (m_ctx->GetBufferType())
        {
        case RayTracing::BT_B8G8R8A8:
            index = y * m_width + x;
            data = (u8*)m_ctx->GetBuffer();
            data += index * (int)BT_B8G8R8A8/8;
            *data++ = (int)color.b;
            *data++ = (int)color.g;
            *data++ = (int)color.r;
            *data = (int)color.a;
            break;
        default:
            break;
        }
    }

}