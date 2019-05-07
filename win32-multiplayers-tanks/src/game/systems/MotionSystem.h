#pragma once

#include "../../core/ecs/ecs.h"
#include "../components/ComponentsMap.h"

using namespace core;
using namespace ecs;

namespace game { namespace logic {

	class MotionSystem : public ecs::ISystem
	{
	private:
		ecs::ECSEngine* engine;

	public:
		MotionSystem(ecs::ECSEngine* engine) : 
			engine(engine)
		{        
		}

		void Update(f32 dt) override
		{
			core::ecs::ComponentsContainer<MotionComponent>* motionСomponents = 
				engine->GetComponentManager()->GetComponentsContainer<MotionComponent>();
        
			for(u32 i = 0; i < motionСomponents->GetSize(); ++i)
			{
				MotionComponent* mc = motionСomponents->Components[i];
				u32 ownerID = mc->getOwnerId();
				TransformComponent* transformСomponents = engine->GetComponentManager()->GetComponent<TransformComponent>(ownerID);
				transformСomponents->Pos *= mc->velocity * dt;
			}
		}
	};

}}