#ifndef __INTERSECT_H__
#define __INTERSECT_H__

#include <memory>
#include <glm/vec3.hpp>

namespace RayTracing
{
    class Node;

    struct IntersectResult
    {
        std::shared_ptr<Node> node{};   //产生交点的节点
        float distance{};               //射线与交点的距离
        glm::vec3 position;              //交点的位置
        glm::vec3 normal;               //交点的发现
    };
}

#endif