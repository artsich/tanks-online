#include <Windows.h>
#include <iostream>
#include <string>
#include "src/core.h"
#include "src/utils/Timer.h"
#include "src/window/Window.h"
#include "src/input/gamecontroller.h"
#include "src/input/KeyboardHandler.h"
#include "src/imageloaders/loadbmp.h"
#include "src/math/vec2.h"

#define TEST_IMAGE_FILE "C:\\Users\\artyo\\source\\repos\\multiplayer-tanks\\Debug\\image.bmp"
#define TEST_TEXT_FILE "C:\\Users\\artyo\\source\\repos\\multiplayer-tanks\\Debug\\text.txt"
#define MY_DEBUG_GAMEPAD 2
#define MY_DEBUG_KEYBOARD 0

namespace core { namespace graphics {

	struct sprite
	{
		core::math::vec2 pos;
		core::math::vec2 size;
	};

	class Rasterization
	{
	private:
		core::window::screen_buffer* buffer;

	public:
		Rasterization(core::window::screen_buffer* buffer) : 
			buffer(buffer) 
		{}

		void draw_rect(float xmin, float xmax, float ymin, float ymax, uint32_t color)
		{
			if (xmin < 0)
			{
				xmin = 0;
			}
			if (ymin < 0)
			{
				ymin = 0;
			}
			if (xmax > buffer->Width)
			{
				xmax = buffer->Width;
			}
			if (ymax > buffer->Height)
			{
				ymax = buffer->Height;
			}

			uint32_t* pixels = ((uint32_t*)buffer->Memory);
			if (!pixels) return;

			for (int y = ymin; y < ymax; ++y)
			{
				for (int x = xmin; x < xmax; ++x)
				{
					pixels[x + y * buffer->Width] = color;
				}
			}
		}
	};
}}

namespace core { namespace physic {

	struct entity
	{
		core::math::vec2 pos;
		core::math::vec2 size;
	};
	//TODO: bug for gamepad infinity stick movable ???
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
				float xStick = controller->StickAverageX;
				float yStick = -controller->StickAverageY;

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
				dy *= speed;
				dy *= speed;

				core::math::vec2& pos = entity.pos;

				pos.x += dx * dt;
				pos.y += dy * dt;
			}		
		}
	}
}}

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPTSTR pCmdLine, int nCmdShow)
{
	core::window::setting_window setting;
	setting.width = 800;
	setting.height = 600;
	setting.windowWidth = 1024;
	setting.windowHeight = 720;

	setting.title = "World of tanks online";
	setting.hInstance = hInstance;

	core::window::Window window(&setting);
	core::input::InputHandler handler;
	window.set_key_listener(&handler);
	core::window::screen_buffer* buffer = window.get_back_buffer();
	core::graphics::Rasterization resterizer(buffer);
	core::controller::input_setup();
	core::controller::game_input* input = core::controller::get_input();

	core::Timer timer;
	float time = 0.0;
	UINT64 frames = 0;
	UINT64 updates = 0;
	float lastTime = timer.elapsed();
	float delta = 0.0f;
	float framePerSecond = 1.0f / 60.0f;
	
	float speed = 126.0f;

	core::physic::entity player;
	player.pos = core::math::vec2(100, 100);
	player.size = core::math::vec2(100, 100);

	while (window.isClose())
	{
		float nowTime = timer.elapsed();
		delta += nowTime - lastTime;
		lastTime = nowTime;

		if (delta > framePerSecond)
		{
			window.processMessage();
			core::controller::update_input();

#if !INPUT_DEBUG
			std::string result = "X: " + std::to_string(input->Controllers[MY_DEBUG_GAMEPAD].StickAverageX*delta)
				+ " Y: " + std::to_string(input->Controllers[MY_DEBUG_GAMEPAD].StickAverageY * delta) + "\n";
			OutputDebugString(result.c_str());
#endif
			core::physic::physic_handle(input, player, speed, delta);

			delta = 0;
			updates++;
		}

		window.clear();

		float xmin = player.pos.x;
		float xmax = xmin + player.size.x;
		float ymin = player.pos.y;
		float ymax = ymin + player.size.y;
		int color = 255 << 16;

		resterizer.draw_rect(xmin, xmax, ymin, ymax, color);
		window.render();
		frames++;

		if (timer.elapsed() - time > 1.0f)
		{
#if FPS_DEBUG
			OutputDebugString((std::to_string(frames) + " fps : " + std::to_string(updates) + " updates\n").c_str());
#endif
			time += 1.0f;
			updates = frames = 0;
		}
	}

	return 0;
}