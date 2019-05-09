#pragma once

#include "../../core/ecs/ecs.h"
#include "../components/ComponentsMap.h"
#include "../Entities.h"

using namespace core;
using namespace ecs;
using namespace math;

namespace game { namespace logic {

	class MotionSystem : public ecs::ISystem
	{
	private:
		ecs::ECSEngine* engine;
		world* WorldMap;

	public:
		MotionSystem(ecs::ECSEngine* engine, world* WorldMap) :
			engine(engine),
			WorldMap(WorldMap)
		{        
		}

		void Update(f32 dt) override
		{
			core::ecs::ComponentsContainer<MotionComponent>* motionСomponents =
				engine->GetComponentManager()->GetComponentsContainer<MotionComponent>();

			for (u32 i = 0; i < motionСomponents->GetSize(); ++i)
			{
				MotionComponent* mc = motionСomponents->Components[i];
				if (!mc->isActive) continue;

				u32 ownerID = mc->getOwnerId();
				TransformComponent* transformСomponents = engine->GetComponentManager()->GetComponent<TransformComponent>(ownerID);
				RigidbodyComponent2D* rb = engine->GetComponentManager()->GetComponent<RigidbodyComponent2D>(ownerID);

				v2 NewP = transformСomponents->ScreenP;
				NewP += mc->velocity * mc->acceleration * dt;
				v2 OriginP = NewP + rb->Size / 2;

				//TODO: Fix 
				if (IsWorldPointEmpty(WorldMap, OriginP))
				{ 
					transformСomponents->ScreenP = NewP;
				}
				else
				{
					if (mc->Auto)
					{
						mc->acceleration = 0.0f;
					}
					//TODO: Need a register who is collise
				}
			}
		}

		bool IsWorldPointEmpty(world* World, v2 P)
		{
			u32 TileX = P.x / World->TileSideInPixels;
			u32 TileY = P.y / World->TileSideInPixels;
			u32 TileValue = GetTileValue(World, TileX, TileY);

			return TileValue == 0;
		}

		u32 GetTileValue(world* World, u32 TestX, u32 TestY)
		{
			u32 Result = 0;
			if (TestX >= 0 && TestX < World->TileChunkCountX && 
				TestY >= 0 && TestY < World->TileChunkCountY)
			{
				Result = World->Tiles[TestY*World->TileChunkCountX + TestX];
			}
			return Result;
		}
	};

}}