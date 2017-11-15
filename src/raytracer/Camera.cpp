#include "Camera.h"
#include "Ray.h"
#include <glm/detail/func_geometric.hpp>
#include "common.h"

namespace RayTracing
{
    Camera::Camera()
    {

    }

    Camera::Camera(glm::vec3 pos, glm::vec3 target, glm::vec3 up, float fov)
        : m_position(pos), m_target(target), m_up(up), m_fov(fov)
    {
        m_right = glm::cross(m_target, m_up);
        m_up = glm::cross(m_right, m_target);
        m_fovScale = (float)tan(fov * 0.5 * M_PI / 180) * 2;
    }

    std::shared_ptr<Ray> Camera::ProductRay(float x, float y)
    {
        //将0~1的坐标映射到 fov上
        auto vx = m_right * float((x - 0.5) * m_fovScale);
        auto vy = m_up * float((y - 0.5) * m_fovScale);
        return std::make_shared<Ray>(m_position, glm::normalize(m_target + vx + vy));
    }

}