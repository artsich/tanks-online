#pragma once

#include "../../core/ecs/ecs.h"
#include "../../core/math/math.h"

struct RigidbodyComponent2D : public core::ecs::Component<RigidbodyComponent2D>
{
	math::v2 Size;

	RigidbodyComponent2D() = default;

	RigidbodyComponent2D(math::v2 Size) : 
		Size(Size)
	{
	}
};