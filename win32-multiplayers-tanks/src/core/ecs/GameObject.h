#pragma once

#include "../core.h"

using GameObjectId = u32;

namespace core { namespace ecs {

	struct GameObject
	{
		GameObjectId Id;
		bool isAlive;
	};

} }