#include "Camera.h"
#include "Ray.h"
#include <glm/detail/func_geometric.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include "common.h"

namespace RayTracing
{
    Camera::Camera()
    {
        m_ray = std::make_shared<Ray>();
    }

    Camera::Camera(glm::vec3 pos, glm::vec3 target, glm::vec3 up, float fov)
        : m_position(pos), m_target(target), m_up(up), m_fov(fov)
    {
        m_right = glm::cross(m_target, m_up);
        m_up = glm::cross(m_right, m_target);
        m_fovScale = (float)tan(fov * 0.5 * M_PI / 180) * 2;

        m_ray = std::make_shared<Ray>();
    }

    std::shared_ptr<Ray> Camera::ProductRay(float x, float y)
    {
        //将0~1的坐标映射到 fov上
        auto vx = m_right * float((x - 0.5) * m_fovScale);
        auto vy = m_up * float((y - 0.5) * m_fovScale);
        m_ray->SetOrigin(m_position);
        m_ray->SetDirection(glm::normalize(m_target + vx + vy));
        return m_ray;
    }

    void Camera::OnMouseMove(float dx, float dy)
    {
        if (dx != 0.f)
        {
            m_position = glm::rotate(m_position, dx, glm::vec3(0.f, 1.f, 0.f));
            m_target = glm::rotate(m_target, dx, glm::vec3(0.f, 1.f, 0.f));
            m_right = glm::cross(m_target, m_up);
            m_up = glm::cross(m_right, m_target);
        }

        if (dy != 0.f)
        {
            m_right = glm::rotate(m_right, dy, m_target);
            m_up = glm::cross(m_right, m_target);
        }
    }

    void Camera::OnKeyDown(unsigned int key)
    {
        switch (key)
        {
        case 'w':
        case 'W':
            m_position.z -= 1;
            break;
        case 's':
        case 'S':
            m_position.z += 1;
        case 'a':
        case 'A':
            m_position.x -= 1;
            break;
        case 'D':
        case 'd':
            m_position.x += 1;
        default:
            break;
        }
    }

    void Camera::OnKeyRelease(unsigned int key)
    {
        
    }
}