#ifndef __INTERSECT_H__
#define __INTERSECT_H__

#include <memory>
#include <glm/vec3.hpp>

namespace RayTracing
{
    class Node;

    struct IntersectResult
    {
        std::shared_ptr<Node> node{};   //��������Ľڵ�
        float distance{};               //�����뽻��ľ���
        glm::vec3 position;              //�����λ��
        glm::vec3 normal;               //����ķ���
    };
}

#endif