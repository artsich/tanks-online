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
#include "src/core/input/KeyboardHandler.h"
#include "src/core/ecs/managers/ComponentManager.h"

#include "src/game/Entities.h"
#include "src/game/components/ComponentsMap.h"
#include "src/game/systems/SystemMap.h"

#include "src/game/GameSetting.h"

using namespace game;
using namespace logic;

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPTSTR pCmdLine, int nCmdShow)
{
#pragma region setting
	core::window::setting_window setting;
	setting.width = GameWindowWidth;
	setting.height = GameWindowHeight;
	setting.windowWidth = 1024;
	setting.windowHeight = 720;
	setting.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
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
	GameMemory.SizeMemory = MB(64);
	GameMemory.Memory = malloc(GameMemory.SizeMemory);

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

//_------First Player
	math::v2 ScreenPlayerPOne = { 100, 100 };
	math::v2 Size = math::v2(60.0, 60.0);
	math::v2 PlayerRespawnP = math::v2(100.0f, 100.0f);
	u32 ControllerIndexP1 = 0;
	game::CreatePlayer(&CManager, ScreenPlayerPOne, Size, PlayerRespawnP, 
		Sprites::PlayerSprite, ControllerIndexP1);

//_------Second Player
	math::v2 ScreenEnemyrPTwo = { 660, 300 };
	math::v2 EnemySize = math::v2(60.0, 60.0);
	math::v2 RespawnEnemyP = math::v2(680, 300);
	u32 ControllerIndexP2 = 1;
	game::CreatePlayer(&CManager, ScreenEnemyrPTwo, EnemySize, RespawnEnemyP, Sprites::PlayerSprite2, ControllerIndexP2);

	ECSEngine ecsEngine(&CManager);
	RenderSystem RenderSystem(&ecsEngine, &rasterizer);
	MotionSystem MotionSystem(&ecsEngine, &World);
	InputSystem  InputSystem(&ecsEngine);
	HealthSystem HealthSystem(&ecsEngine);
	BulletSystem BulletSystem(&ecsEngine);
	ShooterSystem ShooterSystem(&ecsEngine);
	RespawnSystem RespSystem(&ecsEngine);

	ecsEngine.addSystem(&ShooterSystem);
	ecsEngine.addSystem(&InputSystem);
	ecsEngine.addSystem(&MotionSystem);
	ecsEngine.addSystem(&BulletSystem);
	ecsEngine.addSystem(&HealthSystem);
	ecsEngine.addSystem(&RenderSystem);
	ecsEngine.addSystem(&RespSystem);

#pragma endregion

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
			delta = 0;
			updates++;
		}

		ecsEngine.update(delta);
		window.render();
		window.clear();
		frames++;
		if (timer.elapsed() - time > 1.0f)
		{
#if FPS_DEBUG
			OutputDebugString((std::to_string(frames) + " fps : " + \
				std::to_string(updates) + " updates\n").c_str());
#endif
			time += 1.0f;
			updates = frames = 0;
		}
	}

	return 0;
}