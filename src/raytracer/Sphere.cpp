#include "Sphere.h"
#include "Ray.h"
#include <glm/detail/func_geometric.hpp>

namespace RayTracing 
{
    std::shared_ptr<IntersectResult> Sphere::Intersect(std::shared_ptr<Ray> ray)
    {
        using namespace glm;
        vec3 V = ray->GetOrigin() - m_position;
        float dDotV = dot(ray->GetDirection(), V);
        float minDisSqr = dot(V, V) - dot(m_radius, m_radius);
        //方向相反 才能看见
        if (dDotV <= 0)
        {
            auto diff = dDotV * dDotV - minDisSqr;
            if (diff >= 0)
            {
                m_intersectResult->distance = -dDotV - sqrt(diff);
                m_intersectResult->position = ray->GetPoint(m_intersectResult->distance);
                m_intersectResult->node = shared_from_this();
                m_intersectResult->normal = normalize(m_intersectResult->position - m_position);
                return m_intersectResult;
            }
        }

        m_intersectResult->Clear();
        return m_intersectResult;
    }

}