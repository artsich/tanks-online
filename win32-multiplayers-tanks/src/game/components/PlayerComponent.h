#pragma once

#include "../../core/ecs/ecs.h"

struct PlayerComponent : public core::ecs::Component<PlayerComponent>
{
	bool CurrentPlayer;

	PlayerComponent()
	{
		CurrentPlayer = true;
	}

	PlayerComponent(bool CurrentPlayer) : 
		CurrentPlayer(CurrentPlayer)
	{
	}
};