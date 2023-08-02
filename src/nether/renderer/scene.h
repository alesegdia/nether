#pragma once

#include <memory>

#include "nether/renderer/scenenode.h"

namespace nether
{

	class Scene
	{
	public:
		template <typename T, Args... args>
		std::shared_ptr<SceneNode> CreateSceneNode()
		{
			auto newNode = std::make_shared<SceneNode>();
		}
	};
}