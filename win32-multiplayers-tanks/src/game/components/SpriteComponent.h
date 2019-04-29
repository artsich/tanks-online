#pragma once

#include "../ecs/Components.h"
#include "../../core/graphics/rasterizer.h"

namespace game { namespace component {

	//todo: fix sprite
	class SpriteComponent : public game::ecs::Component<SpriteComponent>
	{
		core::graphics::sprite sprite;

		SpriteComponent(core::graphics::sprite sprite) : 
			sprite(sprite)
		{

		}

	};

}}