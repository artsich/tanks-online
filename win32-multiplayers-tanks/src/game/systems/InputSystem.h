#pragma once

#include "../Entities.h"

#include "../../core/ecs/ecs.h"
#include "../../core/math/v3.h"
#include "../../core/input/gamecontroller.h"
#include "../components/MotionComponent.h"

using namespace core;
using namespace controller;

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
		bool WasInput = false;
		for (u32 ControllerIndex = 0;
			ControllerIndex < ArrayCount(input->Controllers);
			++ControllerIndex)
		{
			const game_controller_input* Controller = &input->Controllers[ControllerIndex];

			if (Controller->IsAnalog)
			{
				f32 dx = Controller->StickAverageX;
				f32 dy = -Controller->StickAverageY;
				OnUpdateMotionComponents(math::v2(dx, dy));
				WasInput = true;
				break;
			}
			else
			{
				i32 dx = 0.0, dy = 0.0;
				if (Controller->MoveDown.EndedDown)
				{
					dy = 1;
				}				
				if (Controller->MoveUp.EndedDown)
				{
					dy = -1;
				}				
				if (Controller->MoveRight.EndedDown)
				{
					dx = 1;
				}
				
				if (Controller->MoveLeft.EndedDown)
				{
					dx = -1;
				}

				if (dx || dy)
				{
					OnUpdateMotionComponents(math::v2(dx, dy));
					WasInput = true;
					break;
				}
			}
			
			if (Controller->ActionRight.EndedDown)
			{
				OnPlayerShoot(v2(0.0, 1.0), dt);
			}

			if (Controller->ActionLeft.EndedDown)
			{
				OnPlayerShoot(v2(0.0, -1.0), dt);
			}
			
			if (Controller->ActionUp.EndedDown)
			{
				OnPlayerShoot(v2(1.0, 0.0), dt);
			}

			if (Controller->ActionDown.EndedDown)
			{
				OnPlayerShoot(v2(0.0, 1.0), dt);
			}
		}
		
		if (!WasInput)
		{
			OnUpdateMotionComponents(math::v2(0.0f, 0.0f));
		}
    }

private:

	void OnPlayerShoot(v2 Dir, f32 dt)
	{
		auto PC = engine->GetComponentManager()->GetComponentsContainer<PlayerComponent>();

		for (u32 i = 0; i < PC->GetSize(); ++i)
		{
			if (PC->Components[i]->CurrentPlayer)
			{
				GameObjectId ShooterId = PC->Components[i]->ownerId;
				ShooterComponent* ShootComp = engine->GetComponentManager()->GetComponent<ShooterComponent>(ShooterId);

				if (ShootComp->ReloadTime > ShootComp->ShootSpeed)
				{
					ShootComp->ReloadTime = 0.0;
					v2 O = engine->GetComponentManager()->GetComponent<TransformComponent>(ShooterId)->ScreenP;
					v2 S = engine->GetComponentManager()->GetComponent<RigidbodyComponent2D>(ShooterId)->Size;
					//TODO: Fix this equstion
					O = O + (S / 2.0) * (Dir + 1);
					game::CreateBullet(engine->GetComponentManager(), ShooterId, O, Dir);
					break;
				}
			}			
		}
	}

    void OnUpdateMotionComponents(math::v2 NewVel)
    {
        core::ecs::ComponentsContainer<MotionComponent>* mcs = 
			engine->GetComponentManager()->GetComponentsContainer<MotionComponent>();

		for(u32 i = 0; i < mcs->GetSize(); ++i)
        {
            if(mcs->Components[i]->isActive && !mcs->Components[i]->Auto)
            {
				mcs->Components[i]->velocity = NewVel;
            }
        }
    }
};