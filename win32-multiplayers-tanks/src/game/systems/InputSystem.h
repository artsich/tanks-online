#pragma once

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

public:
    InputSystem(ecs::ECSEngine* engine) :
        engine(engine)
    {
        input = get_input();
    }

    void Update(f32 dt) override
    {
		update_input();
        math::v3 newVelocity = {0, 0, 0};
        updateMotionComponents(newVelocity);
    }

private:
    void updateMotionComponents(math::v3 newVel)
    {
        core::ecs::ComponentsContainer<MotionComponent>* mcs = 
			engine->GetComponentManager()->GetComponentsContainer<MotionComponent>();

		for(u32 i = 0; i < mcs->GetSize(); ++i)
        {
            if(mcs->Components[i]->isActive)
            {
				math::v3* OldVel = &mcs->Components[i]->velocity;
                f32 acceleration = mcs->Components[i]->acceleration;
                *OldVel += newVel * acceleration;
            }
        }
    }
};