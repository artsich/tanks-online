#pragma once

#include "../../core/ecs/ecs.h"
#include "../components/ComponentsMap.h"

class ShooterSystem : public core::ecs::ISystem
{
private:
	core::ecs::ECSEngine* Engine;

public:
	ShooterSystem(core::ecs::ECSEngine* Engine) : 
		Engine(Engine)
	{
	}

	void Update(f32 dt)
	{
		auto Shooters = Engine->GetComponentManager()->GetComponentsContainer<ShooterComponent>();

		for (u32 i = 0; i < Shooters->GetSize(); ++i)
		{
			f32& ShootSpeed = Shooters->Components[i]->ShootSpeed;
			f32& ReloadTime = Shooters->Components[i]->ReloadTime;

			if (ReloadTime < ShootSpeed)
			{
				ReloadTime += dt;
			}
		}
	}
};