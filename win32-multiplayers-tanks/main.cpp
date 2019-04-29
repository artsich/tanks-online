#include <Windows.h>
#include <iostream>
#include <string>
#include "src/core/core.h"
#include "src/core/utils/Timer.h"
#include "src/core/window/Window.h"
#include "src/core/input/gamecontroller.h"
#include "src/core/input/KeyboardHandler.h"
#include "src/core/imageloaders/loadbmp.h"
#include "src/core/graphics/Rasterizer.h"
#include "src/core/math/vec2.h"
#include "src/game/systems/physics_system.h"

#define TEST_IMAGE_FILE "C:\\Users\\artyo\\source\\repos\\multiplayer-tanks\\win32-multiplayers-tanks\\res\\game_tile_set.bmp"
#define TEST_TEXT_FILE "C:\\Users\\artyo\\source\\repos\\multiplayer-tanks\\Debug\\text.txt"

#define GameWindowWidth 800
#define GameWindowHeight 800

core::graphics::texture* cut_texture(core::graphics::texture* source_texture, int x, int y, int w, int h) 
{
	uint32_t* source_buffer = (uint32_t*)source_texture->buffer;
	core::graphics::texture* result = (core::graphics::texture*)malloc(sizeof(core::graphics::texture));
	result->width = w;
	result->height = h;

	uint32_t* result_buffer = (uint32_t*)malloc(sizeof(uint32_t)*w*h);

	for (int yy = y; yy < y + h; ++yy) 
	{
		uint32_t next_row = x + yy * source_texture->width;
		uint32_t* row = (source_buffer + next_row);
		for (int xx = x; xx < x + w; ++xx)
		{
			*result_buffer++ = *row++;
		}
	}
	
	result->buffer = result_buffer;
	return result;
}

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPTSTR pCmdLine, int nCmdShow)
{
#pragma region setting

	core::window::setting_window setting;
	setting.width = GameWindowWidth;
	setting.height = GameWindowHeight;
	setting.windowWidth = 1024;
	setting.windowHeight = 720;
	setting.windowClassName = "MainWindow";
	setting.title = "World of tanks online";
	setting.hInstance = hInstance;

	core::input::InputHandler handler;
	core::window::Window window(&setting);
	core::screen_buffer* buffer = window.get_back_buffer();
	core::graphics::Rasterizer resterizer(buffer);
#pragma endregion

	window.set_key_listener(&handler);
	core::controller::input_setup();
	core::controller::game_input* input = core::controller::get_input();

	core::BmpImage image(TEST_IMAGE_FILE);
	auto header = image.getBitmapHeader();

	core::graphics::texture mainTileSet;
	mainTileSet.buffer = image.getPixels();
	mainTileSet.width = header->Width;
	mainTileSet.height = header->Height;

	core::graphics::sprite tank;
	tank.pos = core::math::vec2(GameWindowWidth / 4, GameWindowHeight / 4);
	tank.texture = *cut_texture(&mainTileSet, 0, 0, 100, 100);

	core::graphics::simple_sprite ss;
	ss.size = { 100, 100 };
	ss.color = 255 << 16 | 255 << 8;

	game::physics::entity player = 
	{ 
		core::math::vec2(100, 100), 
		core::math::vec2(400, 256)
	};

	core::Timer timer;
	float time = 0.0;
	UINT64 frames = 0;
	UINT64 updates = 0;
	float lastTime = timer.elapsed();
	float delta = 0.0f;
	float framePerSecond = 1.0f / 60.0f;
	
	float speed = 128.0f;

	while (window.isClose())
	{
		float nowTime = timer.elapsed();
		delta += nowTime - lastTime;
		lastTime = nowTime;

		if (delta > framePerSecond)
		{
			window.processMessage();
			core::controller::update_input();

			game::physics::physic_handle(input, player, speed, delta);

			delta = 0;
			updates++;
		}

		window.clear();
#if 1

		ss.pos = player.pos;

//		tank.pos = player.pos;
//		resterizer.draw_rect(&tank);
		resterizer.draw_rect(&ss);

#endif

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