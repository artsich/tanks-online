#pragma once

#include "../../core/ecs/ecs.h"
#include "../../core/math/math.h"

struct MotionComponent : public core::ecs::Component<MotionComponent>
{
    f32 acceleration;
    math::v3 velocity;

	MotionComponent() = default;
	MotionComponent(math::v3 velocity, f32 acceleration);
};