#pragma once

#include "../../core/ecs/ecs.h"
#include "../components/ComponentsMap.h"

#include "../../core/graphics/rasterizer.h"

namespace game { namespace logic {

	class RenderSystem : public core::ecs::ISystem
	{
	private:
		core::ecs::ECSEngine* World;
		core::graphics::Rasterizer* Graphics;
	public:
		RenderSystem(core::ecs::ECSEngine* World,
					core::graphics::Rasterizer* Graphics) : 
			World(World),
			Graphics(Graphics)
		{
			f32 ScreenCenterX = 0.5 * (f32)Graphics->buffer->Width;
			f32 ScreenCenterY = 0.5 * (f32)Graphics->buffer->Height;
		}

		void Update(f32 DeltaTime)
		{
			auto RenderCompmonents = World->GetComponentManager()->GetComponentsContainer<RenderComponent>();
			for (u32 i = 0; i < RenderCompmonents->GetSize(); ++i)
			{
				RenderComponent* RendrComponent = RenderCompmonents->Components[i];
				TransformComponent* Pos = World->GetComponentManager()->GetComponent<TransformComponent>(RendrComponent->ownerId);
				if(!Pos) continue;
				Graphics->draw_rect(Pos->ScreenP, RendrComponent->Sprite);
			}
		}
	};

} }