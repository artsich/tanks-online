#pragma once

#include "../../core/ecs/ecs.h"
#include "../../core/math/math.h"

struct TransformComponent : public core::ecs::Component<TransformComponent>
{
    math::v3 Pos;
    math::v3 Rot;
    math::v3 Scale;

	TransformComponent() = default;
	TransformComponent(math::v3 Pos, math::v3 Rot, math::v3 Scale);
};