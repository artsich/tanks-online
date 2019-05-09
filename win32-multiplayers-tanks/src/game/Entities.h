#pragma once

#include "../core/ecs/ecs.h"
#include "../core/math/math.h"
#include "../core/utils/utils.h"
#include "../core/graphics/GeometryPrimitives.h"
#include "../game/components/ComponentsMap.h"

#include "GameSetting.h"

using namespace core;
using namespace ecs;
using namespace math;

namespace game 
{ 
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

	enum Colors
	{
		PLAYER_COLOR  = 0xFFFF00,
		PLAYER_COLOR2 = 0xFF00FF,
		ENEMY_COLOR	  = 0xFF0000,
		BULLET_COLOR  = 0x9d9ea0,
		BLOCK1_COLOR  = 0xd6d8db,
		BLOCK2_COLOR  = 0x73a4ef,
		BLOCK3_COLOR  = 0x323e51,
		BLOCK4_COLOR  = 0x323e51
	};

	enum Sprites
	{
		PlayerSprite = 1,
		PlayerSprite2,
		BulletSprite,
		BlockSprite1,
		BlockSprite2,
		BlockSprite3
	};

	namespace util 
	{
		class GUID
		{
		private:
			static u32 ID_COUNT;

		public:
			static u32 GetID()
			{
				return ID_COUNT;
			}

			static u32 NextId()
			{
				return ++ID_COUNT;
			}
		};
		u32 GUID::ID_COUNT = 0;
	}
	
	class SpriteFactory
	{
	public:
		static core::graphics::simple_sprite* GetSprite(Sprites type)
		{
			static core::graphics::simple_sprite Player = { v2(TILE_SIDE_IN_PIXELS, TILE_SIDE_IN_PIXELS), PLAYER_COLOR };
			static core::graphics::simple_sprite Player2 =  { v2(TILE_SIDE_IN_PIXELS, TILE_SIDE_IN_PIXELS), PLAYER_COLOR2 };
			static core::graphics::simple_sprite Bullet = { v2(BULLET_SIDE_IN_PIXELS, BULLET_SIDE_IN_PIXELS), BULLET_COLOR };

			static core::graphics::simple_sprite Block1 = { v2(TILE_SIDE_IN_PIXELS, TILE_SIDE_IN_PIXELS), BLOCK1_COLOR };
			static core::graphics::simple_sprite Block2 = { v2(TILE_SIDE_IN_PIXELS, TILE_SIDE_IN_PIXELS), BLOCK2_COLOR };
			static core::graphics::simple_sprite Block3 = { v2(TILE_SIDE_IN_PIXELS, TILE_SIDE_IN_PIXELS), BLOCK3_COLOR };

			switch (type)
			{
			case 1:
				return &Player;
			case 2:
				return &Player2;
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

	class EntityBuilder
	{
	private:
		core::ecs::ComponentManager* CManager;
		bool IsBuildNow;
		u32 CurrentID;

	public:
		EntityBuilder(core::ecs::ComponentManager* CManager) :
			CManager(CManager)
		{
		}

		void StartBuild()
		{
			if (!IsBuildNow)
			{
				IsBuildNow = true;
				CurrentID = util::GUID::NextId();
			}
		}

		template<class T, class... ARGS>
		void AddComponent(ARGS&&... Args)
		{
			if (IsBuildNow)
			{
				CManager->AddComponent<T>(CurrentID, std::forward<ARGS>(Args)...);
			}
		}

		GameObject Build()
		{
			if (IsBuildNow)
			{
				IsBuildNow = false;
				return { CurrentID };
			}
			return { INVALID_GAME_OBJECT_ID };
		}
	};
	
	GameObject CreateBlock(core::ecs::ComponentManager* CManager, 
		math::v2 P, 
		math::v2 S, 
		Sprites KindOfSprite)
	{
		EntityBuilder builder(CManager);
		builder.StartBuild();
		builder.AddComponent<TransformComponent>(P);
		builder.AddComponent<RigidbodyComponent2D>(S);
		builder.AddComponent<RenderComponent>(SpriteFactory::GetSprite(KindOfSprite));
		return builder.Build();
	}
	
	GameObject CreateBullet(core::ecs::ComponentManager* CManager, GameObjectId ShooterId, v2 O, v2 D)
	{
		v2 Size(BULLET_SIDE_IN_PIXELS, BULLET_SIDE_IN_PIXELS);
		O += (D * BULLET_SIDE_IN_PIXELS);

		EntityBuilder builder(CManager);
		builder.StartBuild();
		builder.AddComponent<TransformComponent>(O);
		builder.AddComponent<BulletComponent>(BULLET_DAMAGE, ShooterId);
		builder.AddComponent<MotionComponent>(D, BULLET_SPEED, true);
		builder.AddComponent<RigidbodyComponent2D>(Size);
		builder.AddComponent<RenderComponent>(SpriteFactory::GetSprite(Sprites::BulletSprite));
		return builder.Build();
	}

	GameObject CreatePlayer(core::ecs::ComponentManager* CManager, 
		v2 P,
		v2 S,
		v2 RespawnP,
		Sprites Sprite,
		u32 ControllerIndex)
	{
		EntityBuilder builder(CManager);
		builder.StartBuild();
		builder.AddComponent<TransformComponent>(P);
		builder.AddComponent<RigidbodyComponent2D>(S);
		builder.AddComponent<RespawnComponent>(RespawnP);
		builder.AddComponent<ShooterComponent>(SHOOT_SPEED);
		builder.AddComponent<HealthComponent >(DEFAULT_PLAYER_HEALTH, DEFAULT_PLAYER_HEALTH);
		builder.AddComponent<ControllerIndexComponent>(ControllerIndex);
		builder.AddComponent<MotionComponent>(math::v2(0.0, 0.0), DEFAULT_PLAYER_ACCELERATION);
		builder.AddComponent<RenderComponent>(SpriteFactory::GetSprite(Sprite));
		return builder.Build();
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
					CreateBlock(CManager, P, Size, Sprites::BlockSprite1);
					break;
				case 2:
					CreateBlock(CManager, P, Size, Sprites::BlockSprite2);
					break;
				case 3:
					CreateBlock(CManager, P, Size, Sprites::BlockSprite3);
					break;
				default:
					break;
				}				
			}
		}
	}
}