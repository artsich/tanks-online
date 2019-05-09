#pragma once

#include "../../core/ecs/ecs.h"
#include "../components/ComponentsMap.h"
namespace game { namespace logic {

	class RespawnSystem : public core::ecs::ISystem
	{
	private:
		core::ecs::ECSEngine* Engine;

	public:
		RespawnSystem(core::ecs::ECSEngine* Engine) :
			Engine(Engine)
		{
		}

		void Update(f32 dt)
		{
			auto Helths = Engine->GetComponentManager()->GetComponentsContainer<HealthComponent>();

			for (u32 i = 0; i < Helths->GetSize(); ++i)
			{
				auto HC = Helths->Components[i];
				if (HC->Health <= 0 && HC->isActive)
				{
					math::v2 RespawnP = Engine->GetComponentManager()->GetComponent<RespawnComponent>(HC->ownerId)->RespawnP;
					math::v2& P = Engine->GetComponentManager()->GetComponent<TransformComponent>(HC->ownerId)->ScreenP;
					P = RespawnP;
					HC->Health = HC->DefaultHP;
				}
			}
		}
	};

}}