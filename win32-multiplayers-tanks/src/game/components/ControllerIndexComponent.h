#pragma once

#include "../../core/ecs/ecs.h"

struct ControllerIndexComponent : public core::ecs::Component<ControllerIndexComponent>
{
	u32 ControllerIndex;

	ControllerIndexComponent() = default;

	ControllerIndexComponent(u32 ControllerIndex) : 
		ControllerIndex(ControllerIndex)
	{		
	}
};
