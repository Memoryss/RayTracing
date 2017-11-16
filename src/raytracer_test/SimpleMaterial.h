#ifndef __SIMPLE_MATERIAL_H__
#define __SIMPLE_MATERIAL_H__

#include "Material.h"
#include <glm/detail/func_common.hpp>

namespace RayTracing 
{
    /**
    ∆Â≈Ã≤ƒ÷ 
    */
    class SimpleMaterial : public Material
    {
    public:
        SimpleMaterial(float scale) : m_scale(scale) {}

        virtual glm::vec4 ray(std::shared_ptr<Ray> ray, glm::vec3 position, glm::vec3 normal)
        {
            return glm::abs((glm::floor(position.x * 0.1f) + glm::floor(position.z * m_scale)) % 2) < 1 ? glm::vec4{ 0.f, 0.f, 0.f, 255.f } : glm::vec4{ 255.f, 255.f, 255.f, 255.f };
        }

    private:
        float m_scale{};
    };
}

#endif