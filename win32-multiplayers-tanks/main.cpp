#include <Windows.h>
#include <iostream>
#include <string>

#include "src/core/core.h"
#include "src/core/ecs/ecs.h"
#include "src/core/ecs/managers/ComponentManager.h"
#include "src/core/math/math.h"
#include "src/core/utils/Timer.h"
#include "src/core/window/Window.h"
#include "src/core/graphics/Rasterizer.h"
#include "src/core/input/gamecontroller.h"
#include "src/core/imageloaders/loadbmp.h"
#include "src/core/input/KeyboardHandler.h"

#include "src/game/systems/SystemMap.h"
#include "src/game/components/ComponentsMap.h"

#define TEST_IMAGE_FILE "C:\\Users\\artyo\\source\\repos\\multiplayer-tanks\\win32-multiplayers-tanks\\res\\game_tile_set.bmp"
#define TEST_TEXT_FILE "C:\\Users\\artyo\\source\\repos\\multiplayer-tanks\\Debug\\text.txt"

#define GameWindowWidth 800
#define GameWindowHeight 600

const f32 MonitorRefreshHz = 60.0f;
const f32 MsPerSecond = 1.0f / MonitorRefreshHz;

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

INT WinMain(HINSTANCE hInstance, HINSTANCE, LPTSTR pCmdLine, int nCmdShow)
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
#pragma endregion

#pragma region InitEngine
	core::input::InputHandler handler;
	core::window::Window window(&setting);
	core::screen_buffer* buffer = window.get_back_buffer();
	core::graphics::Rasterizer rasterizer(buffer);

	window.set_key_listener(&handler);
	core::controller::input_setup();
	core::controller::game_input* input = core::controller::get_input();

//MEMMORY ALLOCATE
	core::game_memory GameMemory;
	GameMemory.SizeMemory = MB(100);
	GameMemory.Memory = malloc(GameMemory.SizeMemory / 2);

	memory::LinearAllocator LAllocator(GameMemory.Memory, GameMemory.SizeMemory);
	core::ecs::ComponentManager CManager(&LAllocator);
//core::ecs::EntiytManager EManager(GameMemory + LAllocator.SizeMemory, SizeMemory - LAllocator.SizeMemory);

	core::ecs::ECSEngine ecsEngine(&CManager);
	game::logic::RenderSystem RenderSystem(&ecsEngine, &rasterizer);
	ecsEngine.addSystem(&RenderSystem);

#pragma endregion

#pragma region BlockCreate

	core::ecs::GameObject Block {1, true};
	core::ecs::GameObject Block2 { 2, true };

	math::v2 RenderPosition = { 100, 100 };
	math::v2 RenderSize = { 100, 100 };
	u32 Color = 255 << 24;
	auto Sprite = CManager.AddComponent<RenderComponent>(Block.Id, RenderPosition, RenderSize, Color);

	math::v2 RenderPosition2 = { 1.0, 1.0 };
	math::v2 RenderSize2 = { 100, 100 };
	u32 Color2 = 255 << 8;
	auto Sprite2 = CManager.AddComponent<RenderComponent>(Block2.Id, RenderPosition2, RenderSize2, Color2);

	//math::v3 velocity = { 10.0f, 10.f };
	//f32 Acceleration = 16.0f;
	//auto justTest = CManager.AddComponent<MotionComponent>(Block.Id, velocity, Acceleration);

#pragma endregion

#if TEXTURE_TEST
	core::BmpImage image(TEST_IMAGE_FILE);
	auto header = image.getBitmapHeader();

	core::graphics::texture mainTileSet;
	mainTileSet.buffer = image.getPixels();
	mainTileSet.width = header->Width;
	mainTileSet.height = header->Height;

	core::graphics::sprite tank;
	tank.pos = core::math::vec2(GameWindowWidth / 4, GameWindowHeight / 4);
	tank.texture = *cut_texture(&mainTileSet, 0, 0, 100, 100);
#endif

	core::Timer timer;
	float time = 0.0;
	UINT64 frames = 0;
	UINT64 updates = 0;
	float lastTime = timer.elapsed();
	float delta = 0.0f;

	while (window.isClose())
	{
		float nowTime = timer.elapsed();
		delta += nowTime - lastTime;
		lastTime = nowTime;

		if (delta > MsPerSecond)
		{
			window.processMessage();
			core::controller::update_input();
			

			delta = 0;
			updates++;
		}

		window.clear();

		ecsEngine.update(delta);
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