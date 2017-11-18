#ifndef __SCENE_H__
#define __SCENE_H__

#include "Node.h"
#include <vector>

namespace RayTracing
{
	class Scene : public Node
	{
	public:
		virtual std::shared_ptr<IntersectResult> Intersect(std::shared_ptr<Ray> ray) override;
		
		void AddChild(std::shared_ptr<Node> node);

		void RemoveChild(std::shared_ptr<Node> node);

	private:

		std::vector<std::shared_ptr<Node>> m_children;
	};
}

#endif