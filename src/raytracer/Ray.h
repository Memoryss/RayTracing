#ifndef __RAY_H__
#define __RAY_H__

#include <glm/vec3.hpp>

namespace RayTracing {

    class Ray
    {
    public:
        Ray();
        Ray(glm::vec3 &origin, glm::vec3 &direction);

        glm::vec3 GetOrigin() const;
        glm::vec3 GetDirection() const;

        //���ݴ���Ĳ���t ���������ϵ��λ��
        glm::vec3 GetPoint(float t) const;

    private:
        glm::vec3 m_origin;     //���ߵ���ʼλ��
        glm::vec3 m_direction;  //���ߵķ���
    };
}

#endif