#ifndef __SPHERE_H__
#define __SPHERE_H__

#include "Node.h"

namespace RayTracing 
{
    class Sphere : public Node
    {
    public:
        Sphere() {};
        Sphere(glm::vec3 &pos, float radius) : Node(pos), m_radius(radius) {}

        virtual std::shared_ptr<IntersectResult> Intersect(std::shared_ptr<Ray> ray) override;

    private:
        float m_radius{};
    };
}

#endif
