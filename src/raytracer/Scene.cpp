#include "Scene.h"
#include "Node.h"
#include "Intersect.h"
#include "Ray.h"
#include "Light.h"
#include <glm/detail//func_geometric.hpp>

namespace RayTracing
{

    Scene::Scene()
    {
        m_minResult = std::make_shared<IntersectResult>();
        m_shadowResult = std::make_shared<IntersectResult>();
        m_shadowRay = std::make_shared<Ray>();
    }

    std::shared_ptr<IntersectResult> Scene::RayCast(std::shared_ptr<Ray> ray, std::shared_ptr<Light> light)
	{
		float minDistance = FLT_MAX;
        m_minResult->Clear();

		for (auto iter = m_children.begin(); iter != m_children.end(); ++iter)
		{
			auto node = *iter;
			if (node.get() == nullptr)
			{
				continue;
			}
			auto result = node->Intersect(ray);
			if (result->node.get() != nullptr && result->distance < minDistance)
			{
                m_minResult->Clone(result);
				minDistance = result->distance;
			}
		}

        //ÅÐ¶ÏÒõÓ°
        if (m_minResult->node.get() != nullptr)
        {
            m_shadowNode = m_minResult->node;
            m_shadowRay->SetOrigin(m_minResult->position);
            m_shadowRay->SetDirection(glm::normalize(-(light->GetDirection(m_minResult->position))));
            auto result = shadowTest(m_shadowRay);
            if (result->node.get() != nullptr)
            {
                m_minResult->shadowed = true;
            }
        }

		return m_minResult;
	}

	void Scene::AddChild(std::shared_ptr<Node> node)
	{
		if (node.get() != nullptr)
		{
			m_children.push_back(node);
		}
	}

	void Scene::RemoveChild(std::shared_ptr<Node> node)
	{
		if (node.get() != nullptr)
		{
			for (auto iter = m_children.begin(); iter != m_children.end(); ++iter)
			{
				if (iter->get() == node.get())
				{
					m_children.erase(iter);
					break;
				}
			}
		}
	}

    std::shared_ptr<RayTracing::IntersectResult> Scene::shadowTest(std::shared_ptr<Ray> ray)
    {
        for (auto iter = m_children.begin(); iter != m_children.end(); ++iter)
        {
            auto node = *iter;
            if (node.get() == nullptr || node.get() == m_shadowNode.get())
            {
                continue;
            }

            auto result = node->Intersect(ray);
            if (result->node.get() != nullptr)
            {
                return result;
            }
        }

        return m_shadowResult;
    }

}