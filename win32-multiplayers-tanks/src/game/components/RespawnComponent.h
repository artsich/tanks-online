#pragma once

#include "../../core/ecs/ecs.h"
#include "../../core/math/math.h"

struct RespawnComponent : public core::ecs::Component<RespawnComponent>
{
	math::v2 RespawnP;

	RespawnComponent() = default;

	RespawnComponent(math::v2 RespawnP) : 
		RespawnP(RespawnP)
	{
	}
};