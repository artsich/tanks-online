#pragma once

#include "../core.h"

using GameObjectId = u32;
#define INVALID_GAME_OBJECT_ID 999912213
namespace core { namespace ecs {

	struct GameObject
	{
		GameObjectId Id;
	};

} }