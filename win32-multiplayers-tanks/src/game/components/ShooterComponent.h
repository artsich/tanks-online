#pragma once

#include "../../core/ecs//ecs.h"

struct ShooterComponent : public core::ecs::Component<ShooterComponent>
{
	f32 ShootSpeed;
	f32 ReloadTime;
	
	ShooterComponent() = default;
	
	ShooterComponent(f32 ShootSpeed) :
		ShootSpeed(ShootSpeed),
		ReloadTime(0.0)
	{
	}
};