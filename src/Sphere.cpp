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
                auto result = std::make_shared<IntersectResult>();
                result->distance = -dDotV - sqrt(diff);
                result->position = ray->GetPoint(result->distance);
                result->node = shared_from_this();
                result->normal = normalize(result->position - m_position);
                return result;
            }
        }

        return std::make_shared<IntersectResult>();
    }

}