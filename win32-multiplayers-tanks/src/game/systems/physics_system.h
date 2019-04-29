#pragma once

#include "../../core/math/vec2.h"
#include "../../core/input/gamecontroller.h"

namespace game { namespace physics {

	struct entity
	{
		core::math::vec2 pos;
		core::math::vec2 size;
	};

	void physic_handle(core::controller::game_input* input, entity& entity, float speed, float dt)
	{
		for (int controllerIndex = 0;
			controllerIndex < ArrayCount(input->Controllers);
			++controllerIndex)
		{
			core::controller::game_controller_input* controller = core::controller::GetController(input, controllerIndex);

			if (!controller->IsConnected)
			{
				continue;
			}

			if (controller->IsAnalog)
			{
				if (controller->ActionRight.EndedDown)
				{
					entity.pos = core::math::vec2(200, 300);
					continue;
				}

				float xStick = controller->StickAverageX;
				float yStick = controller->StickAverageY;

				core::math::vec2& pos = entity.pos;
				pos.x += xStick * speed * dt;
				pos.y += yStick * speed * dt;
			}
			else
			{
				float dx = 0.0f;
				float dy = 0.0f;
				if (controller->MoveLeft.EndedDown)
				{
					dx = -1.0f;
				}

				if (controller->MoveRight.EndedDown)
				{
					dx = 1.0f;
				}

				if (controller->MoveUp.EndedDown)
				{
					dy = -1.0f;
				}

				if (controller->MoveDown.EndedDown)
				{
					dy = 1.0f;
				}

				dx *= speed;
				dy *= speed;

				core::math::vec2& pos = entity.pos;

				pos.x += dx * dt;
				pos.y += dy * dt;
			}
		}
	}
}}