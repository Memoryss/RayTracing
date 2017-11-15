#ifndef __NODE_H__
#define __NODE_H__

#include <glm/vec3.hpp>
#include "Intersect.h"
#include <memory>

namespace RayTracing
{
    class Ray;

    class Node : public std::enable_shared_from_this<Node>
    {
    public:
        Node() {}
        Node(const glm::vec3 &pos) : m_position(pos) {}

        glm::vec3 GetPosition() const { return m_position; }
        void SetPosition(const glm::vec3 &pos) { m_position = pos; }

        float SqrLength() { return m_position.x * m_position.x + m_position.y * m_position.y + m_position.z * m_position.z; }

        virtual std::shared_ptr<IntersectResult> Intersect(std::shared_ptr<Ray> ray) = 0;

    protected:

        glm::vec3 m_position;
    };
}

#endif
