#pragma once
#include <SceneGraph.h>

namespace scx
{
	class Drawable : public SceneNode<Drawable>
	{
	public:
		Drawable(std::string name) : SceneNode(name) {};
		~Drawable() {};

		virtual void Draw() {  };

		virtual void Update() { };

	};
}