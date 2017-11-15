#include "Ray.h"

namespace RayTracing {

    Ray::Ray()
    {

    }

    Ray::Ray(glm::vec3 &origin, glm::vec3 &direction) : m_origin(origin), m_direction(direction)
    {

    }

    glm::vec3 Ray::GetOrigin() const
    {
        return m_origin;
    }

    glm::vec3 Ray::GetDirection() const
    {
        return m_direction
    }

    glm::vec3 Ray::GetPoint(float t) const
    {
        return m_origin + (t * m_direction);
    }

}