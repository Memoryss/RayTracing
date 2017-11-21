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
        bool shadowed{ false };       //��Ӱ

        void Clear()
        {
            node.reset();
            shadowed = false;
        }

        void Clone(std::shared_ptr<IntersectResult> result)
        {
            this->node = result->node;
            this->distance = result->distance;
            this->position = result->position;
            this->normal = result->normal;
            this->shadowed = result->shadowed;
        }
    };
}

#endif