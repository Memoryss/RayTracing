#include "RayTracer.h"

#include "Scene.h"
#include "Camera.h"
#include <glm/detail/func_geometric.hpp>
#include "Context.h"
#include "Material.h"
#include "Intersect.h"
#include "Node.h"
#include "Ray.h"

namespace RayTracing
{
    RayTracer::RayTracer(std::shared_ptr<Context> ctx)
    {
        assert(ctx.get() != nullptr);
        
        m_ctx = ctx;
    }

    RayTracer::~RayTracer()
    {
        m_ctx.reset();
        m_camera.reset();
        m_scene.reset();
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

    void RayTracer::SetScene(std::shared_ptr<Scene> scene)
    {
		if (scene.get() != nullptr)
		{
			m_scene = scene;
		}
    }

    void RayTracer::SetLight(std::shared_ptr<Light> light)
    {
        m_light = light;
    }

    void RayTracer::RenderDepth(float maxDepth)
    {
        int width = m_ctx->GetWidth();
        int height = m_ctx->GetHeight();

        assert(m_ctx.get() != nullptr || m_ctx->GetBuffer() != nullptr);
        for (int i = 0; i < height; ++i)
        {
            //��Ļ�� ����Ϊ��y��  ����������ϵ�෴
            float ratioY = 1 - float(i) / height;
            for (int j = 0; j < width; ++j)
            {
				float ratioX = float(j) / width;
				auto ray = m_camera->ProductRay(ratioX, ratioY);
				auto result = m_scene->RayCast(ray, m_light);
				if (result->node.get() != NULL)
				{
					glm::vec4 color;
					//�Ѿ�����Ϣӳ�䵽����ϣ�������ʾ ���Ϊ0��ʾ��ɫ ���Խ��  Խ��
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
        int width = m_ctx->GetWidth();
        int height = m_ctx->GetHeight();

        assert(m_ctx.get() != nullptr || m_ctx->GetBuffer() != nullptr);
        for (int i = 0; i < height; ++i)
        {
            //��Ļ�� ����Ϊ��y��  ����������ϵ�෴
            float ratioY = 1 - float(i) / height;
            for (int j = 0; j < width; ++j)
            {
                float ratioX = float(j) / width;
                auto ray = m_camera->ProductRay(ratioX, ratioY);
                auto result = m_scene->RayCast(ray, m_light);
                if (result->node.get() != NULL)
                {
                    glm::vec4 color;
                    //�����Ѿ���һ�� -1~1֮�� ӳ�䵽 0~255
                    color.r = (result->normal.x + 1) * 128;
                    color.g = (result->normal.y + 1) * 128;
                    color.b = (result->normal.z + 1) * 128;
                    color.a = 255;
                    WriteBuffer(j, i, color);
                }
            }
        }
    }

    void RayTracer::RenderNoReflect()
    {
        int width = m_ctx->GetWidth();
        int height = m_ctx->GetHeight();

        assert(m_ctx.get() != nullptr || m_ctx->GetBuffer() != nullptr);
        for (int i = 0; i < height; ++i)
        {
            //��Ļ�� ����Ϊ��y��  ����������ϵ�෴
            float ratioY = 1 - float(i) / height;
            for (int j = 0; j < width; ++j)
            {
                float ratioX = float(j) / width;
                auto ray = m_camera->ProductRay(ratioX, ratioY);
                auto result = m_scene->RayCast(ray, m_light);
                if (result->node.get() != NULL)
                {
                    glm::vec4 color(0.f, 0.f, 0.f, 1.f);
                    if (!result->shadowed)
                    {
                        color = result->node->GetMaterial()->ray(ray, m_light, result->position, result->normal);
                    }
                    color *= 255.f;
                    color = glm::clamp(color, glm::vec4(0.f, 0.f, 0.f, 0.f), glm::vec4(255.f, 255.f, 255.f, 255.f));
                    WriteBuffer(j, i, color);
                }
            }
        }
    }

    void RayTracer::RenderReflect(int maxReflectLevel)
    {
        int width = m_ctx->GetWidth();
        int height = m_ctx->GetHeight();

        assert(m_ctx.get() != nullptr || m_ctx->GetBuffer() != nullptr);
        for (int i = 0; i < height; ++i)
        {
            //��Ļ�� ����Ϊ��y��  ����������ϵ�෴
            float ratioY = 1 - float(i) / height;
            for (int j = 0; j < width; ++j)
            {
                float ratioX = float(j) / width;
                auto ray = m_camera->ProductRay(ratioX, ratioY);
                auto color = traceOnce(ray, maxReflectLevel);
                color *= 255.f;
                color = glm::clamp(color, glm::vec4(0.f, 0.f, 0.f, 0.f), glm::vec4(255.f, 255.f, 255.f, 255.f));
                WriteBuffer(j, i, color);
            }
        }
    }

    glm::vec4 RayTracer::traceOnce(std::shared_ptr<Ray> ray, int &maxReflectLevel)
    {
        auto result = m_scene->RayCast(ray, m_light);
        if (result->node.get() != nullptr)
        {
            glm::vec4 color(0.f, 0.f, 0.f, 1.f);
            if (result->shadowed)
            {
                return color;
            }

            float reflectiveness = result->node->GetMaterial()->GetReflectiveness();
            color = result->node->GetMaterial()->ray(ray, m_light, result->position, result->normal);
            color *= (1 - reflectiveness);  //������ɫ

            //���������Ȳ�Ϊ0 �������·���
            if (maxReflectLevel > 0 && reflectiveness > 0.f)
            {
                //���㷴�䷽��
                auto reflectDir = ray->GetDirection() - 2 * glm::dot(result->normal, ray->GetDirection()) * result->normal;
                //ray = std::make_shared<Ray>(result->position, reflectDir);
                ray->SetOrigin(result->position);
                ray->SetDirection(reflectDir);
                //�ݹ�׷��
                int reflectLevel = maxReflectLevel - 1;
                color += traceOnce(ray, reflectLevel) * reflectiveness;
            }

            return color;
        }
        
        return glm::vec4(0.f, 0.f, 0.f, 1.f);
    }

    void RayTracer::WriteBuffer(int x, int y, const glm::vec4 &color)
    {
        int index = 0;
        u8 *data = nullptr;
        switch (m_ctx->GetBufferType())
        {
        case RayTracing::BT_B8G8R8A8:
            index = y * m_ctx->GetWidth() + x;
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