#pragma once

#include "../core/core.h"

#define GameWindowWidth 1366
#define GameWindowHeight 768

#define GAME_WINDOW_WIDTH GameWindowWidth 
#define GAME_WINDOW_HEIGHT GameWindowHeight

const f32 MonitorRefreshHz = 60.0f;
const f32 MsPerSecond = 1.0f / MonitorRefreshHz;

#define TILES_COUNT_X 17
#define TILES_COUNT_Y 12
#define TILE_SIDE_IN_PIXELS 60
#define TILE_SIDE_IN_METERS 1.4f

#define BULLET_DAMAGE 10
//Speed pixels in ms
#define BULLET_SPEED 1024.0f
#define BULLET_SIDE_IN_PIXELS 20
#define SHOOT_SPEED 0.5f

#define DEFAULT_PLAYER_HEALTH 100
#define DEFAULT_PLAYER_ACCELERATION 128.0f

#define TEST_IMAGE_FILE "C:\\Users\\artyo\\source\\repos\\multiplayer-tanks\\win32-multiplayers-tanks\\res\\game_tile_set.bmp"
#define TEST_TEXT_FILE "C:\\Users\\artyo\\source\\repos\\multiplayer-tanks\\Debug\\text.txt"