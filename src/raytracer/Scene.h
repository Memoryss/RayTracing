#ifndef __SCENE_H__
#define __SCENE_H__

#include <vector>
#include <memory>

namespace RayTracing
{
    struct IntersectResult;
    class Ray;
    class Node;
    class Light;

	class Scene
	{
	public:
        Scene();

		std::shared_ptr<IntersectResult> RayCast(std::shared_ptr<Ray> ray, std::shared_ptr<Light> light);
		
		void AddChild(std::shared_ptr<Node> node);

		void RemoveChild(std::shared_ptr<Node> node);

    protected:
        std::shared_ptr<IntersectResult> shadowTest(std::shared_ptr<Ray> ray);

	private:

		std::vector<std::shared_ptr<Node>> m_children;

        std::shared_ptr<IntersectResult> m_minResult{};
        std::shared_ptr<IntersectResult> m_shadowResult{};
        std::shared_ptr<Ray> m_shadowRay{};
        std::shared_ptr<Node> m_shadowNode{};
	};
}

#endif