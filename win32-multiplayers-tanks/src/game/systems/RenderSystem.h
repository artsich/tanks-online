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
		}

		void Update(f32 DeltaTime)
		{
			auto RenderCompmonents = World->GetComponentManager()->GetComponentsContainer<RenderComponent>();
			for (u32 i = 1; i < RenderCompmonents->GetSize(); ++i)
			{
				core::graphics::simple_sprite* Sprite = &RenderCompmonents->Components[i]->Sprite;
				Graphics->draw_rect(Sprite);
			}
		}
	};

} }