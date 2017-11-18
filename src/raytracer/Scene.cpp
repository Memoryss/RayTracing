#include "Scene.h"

namespace RayTracing
{
	std::shared_ptr<IntersectResult> Scene::Intersect(std::shared_ptr<Ray> ray)
	{
		float minDistance = FLT_MAX;
		auto minResult = std::make_shared<IntersectResult>();

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
				minResult = result;
				minDistance = result->distance;
			}
		}

		return minResult;
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
}