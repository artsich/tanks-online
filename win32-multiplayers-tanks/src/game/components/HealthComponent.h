#pragma once
#include "../../core/ecs/ecs.h"

struct HealthComponent : public core::ecs::Component<HealthComponent>
{
	u32 Health;

	HealthComponent() = default;	
	HealthComponent(u32 Health) : 
		Health(Health)
	{
	}
};