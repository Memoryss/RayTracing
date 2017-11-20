#ifndef __PLANE_H__
#define __PLANE_H__

#include "Node.h"
#include <glm/vec3.hpp>
#include <glm/detail/func_geometric.hpp>
#include "Ray.h"

namespace RayTracing
{
    class Plane : public Node
    {
    public:
        Plane(glm::vec3 normal, float d) : m_normal(glm::normalize(normal)), m_d(d)
        {
            m_position = m_normal * m_d;
        }

        virtual std::shared_ptr<IntersectResult> Intersect(std::shared_ptr<Ray> ray) override
        {
            float nDotR = glm::dot(ray->GetDirection(), m_normal);
            if (nDotR >= 0.f)
            {
                return std::make_shared<IntersectResult>();
            }

			float nDotD = glm::dot(m_normal, ray->GetOrigin() - m_position);
            auto result = std::make_shared<IntersectResult>();
            result->node = shared_from_this();
            result->normal = m_normal;
			result->distance = -nDotD / nDotR; //TODO ?
            result->position = ray->GetPoint(result->distance);
			return result;
        }

    private:
        float m_d;              //ԭ�㵽ƽ������ľ���
        glm::vec3 m_normal;     //ƽ��ķ���
    };

}

#endif
