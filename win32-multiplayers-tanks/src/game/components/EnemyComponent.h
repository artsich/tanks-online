#pragma once
#include "../../core/ecs/ecs.h"

struct EnemyComponent : public core::ecs::Component<EnemyComponent>
{
	EnemyComponent() = default;
};