#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include <memory>
#include <glm/vec4.hpp>
#include <glm/vec3.hpp>

namespace RayTracing
{
    class Ray;

    class Material
    {
    public:
        //’’…‰
        virtual glm::vec4 ray(std::shared_ptr<Ray> ray, glm::vec3 position, glm::vec3 normal) = 0;
    };
}

#endif