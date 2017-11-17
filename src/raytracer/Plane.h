#ifndef __PLANE_H__
#define __PLANE_H__

#include "Node.h"
#include <glm/vec3.hpp>
#include <glm/detail/func_geometric.hpp>

namespace RayTracing
{
    class Plane : public Node
    {
    public:
        Plane(glm::vec3 normal, float d, const std::string &name) : m_normal(glm::normalize(normal)), m_d(d)
        {
            m_position = m_normal * m_d;
            m_name = name;
        }

        virtual std::shared_ptr<IntersectResult> Intersect(std::shared_ptr<Ray> ray) override
        {
            float nDotR = glm::dot(ray->m_direction, m_normal);
            if (nDotR >= 0.f)
            {
                return std::make_shared<IntersectResult>();
            }

            float 
            auto result = std::make_shared<IntersectResult>();
            result->node = std::enable_shared_from_this();
            result->normal = m_normal;
            result->
        }

    private:
        float m_d;              //原点到平面最近的距离
        glm::vec3 m_normal;     //平面的法线
    };

}

#endif
