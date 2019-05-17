#pragma once

#include "../../core/ecs/ecs.h"

struct BulletComponent : public core::ecs::Component<BulletComponent>
{
	u32 Damage;
	//TODO: LOL i'am debil, you have ownerID, OMGo
	GameObjectId ShooterId;

	BulletComponent() = default;

	BulletComponent(u32 Damage, GameObjectId ShooterId) :
		Damage(Damage), 
		ShooterId(ShooterId)
	{
	}
};