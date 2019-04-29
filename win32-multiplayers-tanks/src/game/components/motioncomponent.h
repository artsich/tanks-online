#pragma once

#include "../ecs/Components.h"
#include "../../core/math/vec2.h"

namespace game { namespace component {

	class MotionComponent : public game::ecs::Component<MotionComponent> 
	{
	public:

		MotionComponent(core::math::vec2 pos, core::math::vec2 vel) :
			position(pos), velocity(vel)
		{}

		core::math::vec2 position;
		core::math::vec2 velocity;

	};

}}