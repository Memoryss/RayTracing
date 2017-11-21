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
                m_intersectResult->Clear();
                return m_intersectResult;
            }

			float nDotD = glm::dot(m_normal, ray->GetOrigin() - m_position);
            m_intersectResult->node = shared_from_this();
            m_intersectResult->normal = m_normal;
            m_intersectResult->distance = -nDotD / nDotR; //TODO ?
            m_intersectResult->position = ray->GetPoint(m_intersectResult->distance);
			return m_intersectResult;
        }

    private:
        float m_d;              //原点到平面最近的距离
        glm::vec3 m_normal;     //平面的法线
    };

}

#endif
