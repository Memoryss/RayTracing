#ifndef __PHONG_MATERIAL_H__
#define __PHONG_MATERIAL_H__

#include "Material.h"

namespace RayTracing
{
    class PhongMaterial : public Material
    {
    public:

        virtual glm::vec4 ray(std::shared_ptr<Ray> ray, glm::vec3 position, glm::vec3 normal) override
        {
            
        }

    private:
        glm::vec4 m_diffuse;
        glm::vec4 m_specular;
        glm::vec4 m_shininess;
        glm::vec4 m_reflectiveness;
    };
}

#endif