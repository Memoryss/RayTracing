#ifndef __LIGHT_H__
#define __LIGHT_H__

#include <glm/vec3.hpp>

namespace RayTracing
{
    enum LightType
    {
        LT_DIRECTION,
        LT_POINT,
        LT_SPOT,
    };

    class Light
    {
    public:
        glm::vec3 m_color{1.f, 1.f, 1.f};
        glm::vec3 m_ambient{0.f, 0.f, 0.f};

        virtual glm::vec3 GetDirection(glm::vec3 point) = 0;

        LightType m_type;
    };

    class DirectionLight : public Light
    {
    public:
        DirectionLight() { m_type = LT_DIRECTION; }

        virtual glm::vec3 GetDirection(glm::vec3 point) {
            return m_direction;
        }

        glm::vec3 m_direction;
    };
}

#endif