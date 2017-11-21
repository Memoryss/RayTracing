#ifndef __RAY_H__
#define __RAY_H__

#include <glm/vec3.hpp>

namespace RayTracing {

    class Ray
    {
    public:
        Ray();
        Ray(glm::vec3 &origin, glm::vec3 &direction);

        void SetOrigin(glm::vec3 origin) { m_origin = origin; }
        glm::vec3 GetOrigin() const;

        void SetDirection(glm::vec3 dir) { m_direction = dir; }
        glm::vec3 GetDirection() const;

        //根据传入的参数t 计算射线上点的位置
        glm::vec3 GetPoint(float t) const;

    private:
        glm::vec3 m_origin;     //射线的起始位置
        glm::vec3 m_direction;  //射线的方向
    };
}

#endif