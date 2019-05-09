#pragma once

#include "../../core/ecs/ecs.h"
#include "../../core/math/math.h"
#include "../components/ComponentsMap.h"

using namespace math;

namespace game { namespace logic {

	class BulletSystem : public core::ecs::ISystem
	{
	private:
		core::ecs::ECSEngine* Engine;

	public:
		BulletSystem(core::ecs::ECSEngine* Engine) :
			Engine(Engine)
		{
		}

		void Update(f32 dt)
		{
			auto Bullets = Engine->GetComponentManager()->GetComponentsContainer<BulletComponent>();
			auto LiveEntities = Engine->GetComponentManager()->GetComponentsContainer<HealthComponent>();

			for (u32 i = 0; i < Bullets->GetSize(); ++i)
			{
				if (!Bullets->Components[i]->isActive) continue;

				auto BulletRB = Engine->GetComponentManager()->GetComponent<RigidbodyComponent2D>(Bullets->Components[i]->ownerId);
				auto BulletTranform = Engine->GetComponentManager()->GetComponent<TransformComponent>(Bullets->Components[i]->ownerId);
				auto BulletInfo = Engine->GetComponentManager()->GetComponent<BulletComponent>(Bullets->Components[i]->ownerId);

				v2 A1 = BulletTranform->ScreenP;
				v2 A2 = A1 + BulletRB->Size;

				for (u32 j = 0; j < LiveEntities->GetSize(); ++j)
				{
					auto TargetHealth = LiveEntities->Components[j];
					u32 TargetId = TargetHealth->ownerId;
					auto TargetRB = Engine->GetComponentManager()->GetComponent<RigidbodyComponent2D>(TargetId);
					auto TargetTransform = Engine->GetComponentManager()->GetComponent<TransformComponent>(TargetId);

					v2 B1 = TargetTransform->ScreenP;
					v2 B2 = B1 + TargetRB->Size;

					if (IsHit(A1, B1, A2, B2) ||
						IsHit(B1, A1, B2, A1))
					{
						if (TargetHealth->Health > 0)
						{
							TargetHealth->Health -= BulletInfo->Damage;
							Engine->GetComponentManager()->DeactivateCompoenents(Bullets->Components[i]->ownerId);
						}
					}
				}
			}
		}

	private:

		bool IsHit(v2& a1, v2& b1, v2& a2, v2& b2)
		{
			if (a1.x < b2.x && a2.x > b1.x &&
				a1.y < b2.y && a2.y > b1.y)
			{
				return true;
			}

			return false;
		}
	};
}}