#pragma once

#include "../../core/ecs/ecs.h"
#include "../components/ComponentsMap.h"

class HealthSystem : public core::ecs::ISystem
{
private:
	core::ecs::ECSEngine* Engine;

public:
	HealthSystem(core::ecs::ECSEngine* Engine) :
		Engine(Engine)
	{
	}

	void Update(f32 dt)
	{
		auto DiedEntities = Engine->GetComponentManager()->GetComponentsContainer<HealthComponent>();
	}

};