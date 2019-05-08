#pragma once

#include "../../core/ecs/ecs.h"
#include "../../core/math/math.h"

struct TransformComponent : public core::ecs::Component<TransformComponent>
{
    math::v2 ScreenP;

	TransformComponent() = default;

	TransformComponent(math::v2 P)
	{
		ScreenP = P;
	}
};