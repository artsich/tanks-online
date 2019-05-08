#pragma once

#include "../../core/ecs/ecs.h"
#include "../../core/math/math.h"

struct MotionComponent : public core::ecs::Component<MotionComponent>
{
	bool Auto;
	f32 acceleration;
    math::v2 velocity;

	MotionComponent() = default;

	MotionComponent(math::v2 velocity, f32 acceleration, bool Auto = false) :
		acceleration(acceleration),
		velocity(velocity),
		Auto(Auto)
	{
	}
};