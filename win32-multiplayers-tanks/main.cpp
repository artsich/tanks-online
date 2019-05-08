#include <Windows.h>
#include <iostream>
#include <string>

#include "src/core/core.h"
#include "src/core/ecs/ecs.h"
#include "src/core/math/math.h"
#include "src/core/utils/Timer.h"
#include "src/core/window/Window.h"
#include "src/core/graphics/Rasterizer.h"
#include "src/core/input/gamecontroller.h"
#include "src/core/imageloaders/loadbmp.h"
#include "src/core/input/KeyboardHandler.h"
#include "src/core/ecs/managers/ComponentManager.h"

#include "src/game/Entities.h"
#include "src/game/components/ComponentsMap.h"
#include "src/game/systems/SystemMap.h"

#include "src/game/GameSetting.h"

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

#pragma endregion

#pragma region WorldCreating

	u32 WorldMap[TILES_COUNT_X * TILES_COUNT_Y] =
	{
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 1,
		1, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 3, 0, 3, 0, 0, 1,
		1, 0, 3, 0, 0, 0, 3, 0, 0, 3, 3, 3, 0, 3, 3, 3, 1,
		1, 0, 3, 0, 0, 3, 3, 0, 0, 3, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 3, 3, 0, 0, 3, 3, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 3, 3, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 3, 3, 0, 0, 3, 3, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 0, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	};

	game::world World;
	World.Tiles = WorldMap;
	World.TileChunkCountX = TILES_COUNT_X;
	World.TileChunkCountY = TILES_COUNT_Y;	
	World.TileSideInPixels = TILE_SIDE_IN_PIXELS;
	World.TileSideInMeters = TILE_SIDE_IN_METERS;
	World.MetersToPixels = (f32)(World.TileSideInPixels / World.TileSideInMeters);

	LoadMap(&CManager, &World);

//_------Player

	math::v2 ScreenPlayerP = { 100, 100 };
	math::v2 Size = math::v2(60.0, 60.0);
	f32 PlayerAcceleration = 128;
	game::CreatePlayer(&CManager, ScreenPlayerP, Size, PlayerAcceleration);

	math::v2 ScreenEnemyrP = { 660, 300 };
	math::v2 EnemySize = math::v2(60.0, 60.0);
	f32 EnemyAcceleration = 0.0;
	game::CreateEnemy(&CManager, ScreenEnemyrP, EnemySize, EnemyAcceleration);

//End Player
	
	using namespace game;
	using namespace logic;

	ECSEngine ecsEngine(&CManager);
	RenderSystem RenderSystem(&ecsEngine, &rasterizer);
	MotionSystem MotionSystem(&ecsEngine, &World);
	InputSystem  InputSystem(&ecsEngine);
	HealthSystem HealthSystem(&ecsEngine);
	BulletSystem BulletSystem(&ecsEngine);
	ShooterSystem ShooterSystem(&ecsEngine);

	ecsEngine.addSystem(&ShooterSystem);
	ecsEngine.addSystem(&InputSystem);
	ecsEngine.addSystem(&MotionSystem);
	ecsEngine.addSystem(&BulletSystem);
	ecsEngine.addSystem(&HealthSystem);
	ecsEngine.addSystem(&RenderSystem);

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
			ecsEngine.update(delta);
			window.render();
			window.clear();
			delta = 0;
			updates++;
		}


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