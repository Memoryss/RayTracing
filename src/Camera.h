#ifndef __CAMERA_H__
#define __CAMERA_H__

#include <memory>
#include <glm/vec3.hpp>

namespace RayTracing
{
    class Ray;

    class Camera
    {
    public:
        Camera();
        Camera(glm::vec3 pos, glm::vec3 target, glm::vec3 up, float fov);

        std::shared_ptr<Ray> ProductRay(float x, float y);

    private:
        glm::vec3 m_position;   //���λ��
        glm::vec3 m_target;     //�������
        glm::vec3 m_up;         //���up����
        glm::vec3 m_right;      //���������
        float m_fov;            //���fov�ӽ�
        float m_fovScale;       //ת���м�ֵ���������
    };
}

#endif