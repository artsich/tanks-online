#pragma once

#include "../Entities.h"

#include "../../core/ecs/ecs.h"
#include "../../core/math/v3.h"
#include "../../core/input/gamecontroller.h"
#include "../components/MotionComponent.h"

using namespace core;
using namespace controller;

namespace game { namespace logic {

	class InputSystem : public ecs::ISystem
	{
	private:
		const game_input* input;
		ecs::ECSEngine* engine;
		f32 ShootLags;

	public:
		InputSystem(ecs::ECSEngine* engine) :
			engine(engine)
		{
			input = get_input();
		}

		void Update(f32 dt) override
		{
			update_input();

			//TODO: i < ControllerIndexContainer.GetSize();
			for (u32 ControllerIndex = 0;
				ControllerIndex < 2;//ArrayCount(input->Controllers);
				++ControllerIndex)
			{
				const game_controller_input* Controller = &input->Controllers[ControllerIndex];

				v2 V = {};
				if (Controller->IsAnalog)
				{
					V.x = Controller->StickAverageX;
					V.y = -Controller->StickAverageY;
				}
				else
				{
					if (Controller->MoveDown.EndedDown)
					{
						V.y = 1;
					}
					if (Controller->MoveUp.EndedDown)
					{
						V.y = -1;
					}
					if (Controller->MoveRight.EndedDown)
					{
						V.x = 1;
					}
					if (Controller->MoveLeft.EndedDown)
					{
						V.x = -1;
					}
				}

				OnUpdateMotionComponents(ControllerIndex, V);

				if (Controller->ActionRight.EndedDown)
				{
					OnPlayerShoot(ControllerIndex, v2(1.0, 0.0), dt);
				}

				if (Controller->ActionLeft.EndedDown)
				{
					OnPlayerShoot(ControllerIndex, v2(-1.0, 0.0), dt);
				}

				if (Controller->ActionUp.EndedDown)
				{
					OnPlayerShoot(ControllerIndex, v2(0.0, -1.0), dt);
				}

				if (Controller->ActionDown.EndedDown)
				{
					OnPlayerShoot(ControllerIndex, v2(0.0, 1.0), dt);
				}
			}
		}

	private:

		void OnPlayerShoot(u32 ControllerIndex, v2 Dir, f32 dt)
		{
			core::ecs::ComponentsContainer<ControllerIndexComponent>* CICContainer =
				engine->GetComponentManager()->GetComponentsContainer<ControllerIndexComponent>();

			if (CICContainer->GetSize() <= ControllerIndex) return;

			ControllerIndexComponent* CIC = CICContainer->Components[ControllerIndex];
			if (CIC->isActive)
			{
				GameObjectId ShooterId = CIC->ownerId;
				ShooterComponent* ShootComp = engine->GetComponentManager()->GetComponent<ShooterComponent>(ShooterId);

				if (ShootComp->ReloadTime > ShootComp->ShootSpeed)
				{
					ShootComp->ReloadTime = 0.0;
					v2 O = engine->GetComponentManager()->GetComponent<TransformComponent>(ShooterId)->ScreenP;
					v2 S = engine->GetComponentManager()->GetComponent<RigidbodyComponent2D>(ShooterId)->Size;
					O = O + (S / 2.0) * (Dir + 1);
					CreateBullet(engine->GetComponentManager(), ShooterId, O, Dir);
				}
			}
		}

		void OnUpdateMotionComponents(u32 ControllerIndex, math::v2 NewVel)
		{
			core::ecs::ComponentsContainer<ControllerIndexComponent>* CICContainer =
				engine->GetComponentManager()->GetComponentsContainer<ControllerIndexComponent>();

			if (CICContainer->GetSize() <= ControllerIndex) return;

			ControllerIndexComponent* CIC = CICContainer->Components[ControllerIndex];
			if (CIC->isActive)
			{
				auto mcs = engine->GetComponentManager()->GetComponent<MotionComponent>(CIC->ownerId);
				mcs->velocity = NewVel;
			}
		}

	};
}}