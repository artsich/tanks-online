#pragma once

#include "../core/ecs/ecs.h"
#include "../core/math/math.h"
#include "../core/graphics/GeometryPrimitives.h"
#include "../game/components/ComponentsMap.h"

#include "GameSetting.h"

using namespace core;
using namespace ecs;
using namespace math;

namespace game 
{ 
	enum Colors
	{
		PLAYER_COLOR = 0xFFFF00,
		ENEMY_COLOR	 = 0xFF0000,
		BULLET_COLOR = 0x9d9ea0,
		BLOCK1_COLOR = 0xd6d8db,
		BLOCK2_COLOR = 0x73a4ef,
		BLOCK3_COLOR = 0x323e51,
		BLOCK4_COLOR = 0x323e51
	};

	enum Sprites
	{
		PlayerSprite = 1,
		EnemySprite,
		BulletSprite,
		BlockSprite1,
		BlockSprite2,
		BlockSprite3
	};

	class SpriteFactory
	{
	public:
		static core::graphics::simple_sprite* GetSprite(Sprites type)
		{
			static core::graphics::simple_sprite Player = { v2(TILE_SIDE_IN_PIXELS, TILE_SIDE_IN_PIXELS), PLAYER_COLOR };
			static core::graphics::simple_sprite Enemy =  { v2(TILE_SIDE_IN_PIXELS, TILE_SIDE_IN_PIXELS), ENEMY_COLOR };
			static core::graphics::simple_sprite Bullet = { v2(BULLET_SIDE_IN_PIXELS, BULLET_SIDE_IN_PIXELS), BULLET_COLOR };

			static core::graphics::simple_sprite Block1 = { v2(TILE_SIDE_IN_PIXELS, TILE_SIDE_IN_PIXELS), BLOCK1_COLOR };
			static core::graphics::simple_sprite Block2 = { v2(TILE_SIDE_IN_PIXELS, TILE_SIDE_IN_PIXELS), BLOCK2_COLOR };
			static core::graphics::simple_sprite Block3 = { v2(TILE_SIDE_IN_PIXELS, TILE_SIDE_IN_PIXELS), BLOCK3_COLOR };

			switch (type)
			{
			case 1:
				return &Player;
			case 2:
				return &Enemy;
			case 3:
				return &Bullet;
			case 4:
				return &Block1;
			case 5:
				return &Block2;
			case 6:
				return &Block3;
			default:
				return nullptr;
			}
		}
	};


	struct world
	{
		u32 ChunkShift;
		u32 ChunkMask;
		i32 ChunkDim;

		f32 TileSideInMeters;
		i32 TileSideInPixels;
		f32 MetersToPixels;

		//TODO:: Remove no used field
		i32 TileChunkCountX;
		i32 TileChunkCountY;

		u32* Tiles;
	};

	static u32 GetUID()
	{
		static u32 ID_COUNT = 0;
		return ID_COUNT++;
	}

	GameObject CreateBlock(core::ecs::ComponentManager* CManager, 
		math::v2 P, 
		math::v2 S, 
		graphics::simple_sprite* sprite)
	{
		u32 CurrentGameObjectId = GetUID();

		CManager->AddComponent<TransformComponent>(CurrentGameObjectId, P);
		CManager->AddComponent<RigidbodyComponent2D>(CurrentGameObjectId, S);
		CManager->AddComponent<RenderComponent>(CurrentGameObjectId, sprite);

		return { CurrentGameObjectId };
	}
	
	GameObject CreateBullet(core::ecs::ComponentManager* CManager, GameObjectId ShooterId, v2 P, v2 D)
	{
		static f32 A = 1000.0;
		u32 CurrentId = GetUID();
		v2 Size(BULLET_SIDE_IN_PIXELS, BULLET_SIDE_IN_PIXELS);

		P += (D * BULLET_SIDE_IN_PIXELS);

		CManager->AddComponent<BulletComponent>(CurrentId, BULLET_DAMAGE, ShooterId);

		CManager->AddComponent<TransformComponent>(CurrentId, P);
		CManager->AddComponent<MotionComponent>(CurrentId, D, A, true);
		CManager->AddComponent<RigidbodyComponent2D>(CurrentId, Size);
		CManager->AddComponent<RenderComponent>(CurrentId, SpriteFactory::GetSprite(Sprites::BulletSprite));
		return { CurrentId };
	}

	GameObject CreateLiveEntity(core::ecs::ComponentManager* CManager,
		math::v2 P,
		math::v2 S,
		f32 Acceleration,
		bool AutoMovable,
		Sprites KindOfSprite) 
	{
		u32 CurrentGameObjectId = GetUID();

		CManager->AddComponent<HealthComponent>(CurrentGameObjectId, DEFAULT_PLAYER_HEALTH);
		CManager->AddComponent<ShooterComponent>(CurrentGameObjectId, SHOOT_SPEED);
		CManager->AddComponent<TransformComponent>(CurrentGameObjectId, P);
		CManager->AddComponent<RigidbodyComponent2D>(CurrentGameObjectId, S);
		CManager->AddComponent<MotionComponent>(CurrentGameObjectId, math::v2(0.0, 0.0), Acceleration, AutoMovable);
		CManager->AddComponent<RenderComponent>(CurrentGameObjectId, SpriteFactory::GetSprite(KindOfSprite));

		return { CurrentGameObjectId };
	}

	GameObject CreateEnemy(core::ecs::ComponentManager* CManager,
		math::v2 P,
		math::v2 S,
		f32 Acceleration)
	{
		u32 CurrentGameObjectId = GetUID();

		//TODO// enemy shooter??
		CManager->AddComponent<ShooterComponent>(CurrentGameObjectId, SHOOT_SPEED);

		CManager->AddComponent<EnemyComponent>(CurrentGameObjectId);
		CManager->AddComponent<HealthComponent >(CurrentGameObjectId, DEFAULT_PLAYER_HEALTH);
		
		CManager->AddComponent<TransformComponent>(CurrentGameObjectId, P);
		CManager->AddComponent<RigidbodyComponent2D>(CurrentGameObjectId, S);
		CManager->AddComponent<MotionComponent>(CurrentGameObjectId, math::v2(0.0, 0.0), Acceleration, true);
		CManager->AddComponent<RenderComponent>(CurrentGameObjectId, SpriteFactory::GetSprite(Sprites::EnemySprite));

		return { CurrentGameObjectId };
	}

	GameObject CreatePlayer(core::ecs::ComponentManager* CManager, 
		math::v2 P,
		math::v2 S,
		f32 Acceleration)
	{
		u32 CurrentGameObjectId = GetUID();

		CManager->AddComponent<HealthComponent >(CurrentGameObjectId, DEFAULT_PLAYER_HEALTH);
		CManager->AddComponent<ShooterComponent>(CurrentGameObjectId, SHOOT_SPEED);
		CManager->AddComponent<PlayerComponent>(CurrentGameObjectId);
		CManager->AddComponent<TransformComponent>(CurrentGameObjectId, P);
		CManager->AddComponent<RigidbodyComponent2D>(CurrentGameObjectId, S);
		CManager->AddComponent<MotionComponent>(CurrentGameObjectId, math::v2(0.0, 0.0), Acceleration);
		CManager->AddComponent<RenderComponent>(CurrentGameObjectId, SpriteFactory::GetSprite(Sprites::PlayerSprite));

		return { CurrentGameObjectId };
	}

	void LoadMap(core::ecs::ComponentManager* CManager, world* World)
	{
		u32 TileSideInPixels = World->TileSideInPixels;
		math::v2 Size(World->TileSideInPixels, World->TileSideInPixels);

		for (u32 y = 0; y < World->TileChunkCountY; ++y)
		{
			for (u32 x = 0; x < World->TileChunkCountX; ++x)
			{
				u32 Value = World->Tiles[x + y * World->TileChunkCountX];
				math::v2 P(x * TileSideInPixels, y * TileSideInPixels);
				
				switch (Value)
				{
				case 1:
					CreateBlock(CManager, P, Size, SpriteFactory::GetSprite(Sprites::BlockSprite1));
					break;
				case 2:
					CreateBlock(CManager, P, Size, SpriteFactory::GetSprite(Sprites::BlockSprite2));
					break;
				case 3:
					CreateBlock(CManager, P, Size, SpriteFactory::GetSprite(Sprites::BlockSprite3));
					break;
				default:
					break;
				}				
			}
		}
	}



}