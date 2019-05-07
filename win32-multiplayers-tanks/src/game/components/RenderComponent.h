#pragma once

#include "../../core/ecs/ecs.h"
#include "../../core/math/math.h"

//TODO: Make primitive directory
#include "../../core/graphics/Rasterizer.h"

struct RenderComponent : public core::ecs::Component<RenderComponent>
{
	core::graphics::simple_sprite Sprite;

	RenderComponent() = default;
	RenderComponent(math::v2 Pos, math::v2 Size, u32 Color);
};