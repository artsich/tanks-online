#pragma once

#include "../../core/ecs/ecs.h"

struct BulletComponent : public core::ecs::Component<BulletComponent>
{
	u32 Damage;
	GameObjectId ShooterId;

	BulletComponent() = default;

	BulletComponent(u32 Damage, GameObjectId ShooterId) :
		Damage(Damage), 
		ShooterId(ShooterId)
	{
	}
};