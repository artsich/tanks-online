#pragma once

#include <Windows.h>
#include <Xinput.h>	

#include "../core.h"

#define XINPUT1_4 "xinput1_4.dll"
#define XINPUT1_3 "xinput1_3.dll"
#define XINPUT9_1_0 "xinput9_1_0.dll"

namespace core { namespace controller {

#define VK_MOVE_UP		'W'
#define VK_MOVE_DOWN	'S'
#define VK_MOVE_LEFT	'A'
#define VK_MOVE_RIGHT	'D'
#define VK_FIRE			'F'

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

				game_button_state LeftShoulder;
				game_button_state RightShoulder;

				game_button_state Start;
				game_button_state Back;
			};
		};
	};

	struct game_input
	{
//		float dtForFrame;
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