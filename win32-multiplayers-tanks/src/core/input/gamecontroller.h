#pragma once

#include <Windows.h>
#include <Xinput.h>	

#include "../core.h"

namespace core { namespace controller {

#define XINPUT1_4 "xinput1_4.dll"
#define XINPUT1_3 "xinput1_3.dll"
#define XINPUT9_1_0 "xinput9_1_0.dll"

#define VK_MOVE_UP		'W'
#define VK_MOVE_DOWN	'S'
#define VK_MOVE_LEFT	'A'
#define VK_MOVE_RIGHT	'D'
#define VK_LEFT_FIRE	'J'
#define VK_RIGHT_FIRE	'L'
#define VK_UP_FIRE		'I'
#define VK_DOWN_FIRE	'K'

#define START_GAMEPAD_INDEX 1
#define KEYBOARD_INDEX 0

	struct game_button_state
	{
		int HalfTransiotionCount;
		bool EndedDown;
	};

	struct game_controller_input
	{
		bool IsAnalog;
		bool IsConnected;
		float StickAverageX;
		float StickAverageY;

		union
		{
			game_button_state Buttons[12];
			struct
			{
				game_button_state MoveUp;
				game_button_state MoveDown;
				game_button_state MoveLeft;
				game_button_state MoveRight;

				game_button_state ActionUp;
				game_button_state ActionDown;
				game_button_state ActionLeft;
				game_button_state ActionRight;
			};
		};
	};

	struct game_input
	{
		int32_t MouseX, MouseY;

		game_button_state Mousebuttons[5];
		game_controller_input Controllers[5];
	};

	static void Win32LoadXInput();
	void input_setup();
	void update_input(/*game_input* controller*/);
	game_input* get_input();
	game_controller_input* GetController(game_input* Input, int ControllerIndex);

} }