#ifndef __LIGHT_H__
#define __LIGHT_H__

#include <glm/vec3.hpp>

namespace RayTracing
{
    class Light
    {
        //Light

    protected:
        glm::vec3 m_diffuse{};
        glm::vec3 m_ambient{};
        glm::vec3 m_specular{};
    };
}

#endif