#pragma once
#include "../../core/ecs/ecs.h"

struct HealthComponent : public core::ecs::Component<HealthComponent>
{
	u32 Health;
	u32 DefaultHP;

	HealthComponent() = default;	
	HealthComponent(u32 Health, u32 DefaultHP) :
		Health(Health),
		DefaultHP(DefaultHP)
	{
	}
};