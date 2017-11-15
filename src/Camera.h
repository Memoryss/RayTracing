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
        glm::vec3 m_position;   //相机位置
        glm::vec3 m_target;     //相机朝向
        glm::vec3 m_up;         //相机up向量
        glm::vec3 m_right;      //相机右向量
        float m_fov;            //相机fov视角
        float m_fovScale;       //转化中间值，方面计算
    };
}

#endif