#include "RenderComponent.h"

RenderComponent::RenderComponent(math::v2 Pos, math::v2 Size, u32 Color)
{
	Sprite.pos = Pos;
	Sprite.size = Size;
	Sprite.color = Color;
}