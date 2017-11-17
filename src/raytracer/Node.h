#ifndef __NODE_H__
#define __NODE_H__

#include <glm/vec3.hpp>
#include <string>
#include "Intersect.h"
#include <memory>

namespace RayTracing
{
    class Ray;

    class Material;

    class Node : public std::enable_shared_from_this<Node>
    {
    public:
        Node() {}
        Node(const glm::vec3 &pos, const std::string &name) : m_position(pos), m_name(name) {}

        glm::vec3 GetPosition() const { return m_position; }
        void SetPosition(const glm::vec3 &pos) { m_position = pos; }

        std::shared_ptr<Material> GetMaterial() const { return m_material; }
        void SetMaterial(std::shared_ptr<Material> material) { m_material = material; }

        float SqrLength() { return m_position.x * m_position.x + m_position.y * m_position.y + m_position.z * m_position.z; }

        virtual std::shared_ptr<IntersectResult> Intersect(std::shared_ptr<Ray> ray) = 0;

    protected:

        glm::vec3 m_position{};

        std::shared_ptr<Material> m_material;

        std::string m_name{};
    };
}

#endif
