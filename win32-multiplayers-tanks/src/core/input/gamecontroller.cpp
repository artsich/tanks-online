#include "gamecontroller.h"
#include "KeyboardHandler.h"
#include <string>

namespace core { namespace controller { 

#define X_INPUT_GET_STATE(name) DWORD WINAPI name(DWORD dwUserIndex, XINPUT_STATE* pState)
	typedef X_INPUT_GET_STATE(x_input_get_state);
	X_INPUT_GET_STATE(xInputGetStateStub)
	{
		return ERROR_DEVICE_NOT_CONNECTED;
	}
	x_input_get_state* XInputGetState_ = xInputGetStateStub;
#define XInputGetState XInputGetState_

#define X_INPUT_SET_STATE(name) DWORD WINAPI name(DWORD dwUserIndex, XINPUT_VIBRATION* pVibration)
	typedef X_INPUT_SET_STATE(x_input_set_state);
	X_INPUT_SET_STATE(xInputSetStateStub)
	{
		return ERROR_DEVICE_NOT_CONNECTED;
	}
	x_input_set_state* XInputSetState_ = xInputSetStateStub;
#define XInputSetState XInputSetState_

	static game_input Input[2] = {};
	static game_input* NewInput = nullptr;
	static game_input* OldInput = nullptr;
	 
	static void Win32LoadXInput()
	{
		HMODULE XInputLibrary = LoadLibraryA(XINPUT1_4);

		if (!XInputLibrary)
		{
			XInputLibrary = LoadLibraryA(XINPUT1_3);
		}

		if (!XInputLibrary)
		{
			XInputLibrary = LoadLibraryA(XINPUT9_1_0);
		}

		if (XInputLibrary)
		{
			XInputGetState = (x_input_get_state*)GetProcAddress(XInputLibrary, "XInputGetState");
			if (!XInputGetState)
			{
				XInputGetState = xInputGetStateStub;
			}

			XInputSetState = (x_input_set_state*)GetProcAddress(XInputLibrary, "XInputSetState");
			if (!XInputSetState) { XInputSetState = xInputSetStateStub; }
		}
	}
	//[I0 - d; I0 + d]
	static float Win32ProcessXInputStickValue(SHORT Value, SHORT DeadZoneThreshould)
	{
		float Result = 0;
		if (Value < -DeadZoneThreshould)
		{
			Result = (float)Value / 32768.0f;
		}
		else if (Value > DeadZoneThreshould)
		{
			Result = (float)Value / 32768.0f;
		}

		return(Result);
	}


	//TODO: Refactor isdown
	static void Win32ProcessKeyboardMessage(game_button_state* NewState, DWORD IsDown)
	{
		if (NewState->EndedDown != IsDown)
		{
			NewState->EndedDown = IsDown;
	//		OutputDebugString(("\nKEY DEBUG: " + std::to_string(IsDown)).c_str());
		}
	}

	static void keyboard_process(game_controller_input* controller)
	{
		Win32ProcessKeyboardMessage(&controller->MoveUp, 
			core::input::InputHandler::isKeyPressed(VK_MOVE_UP));

		Win32ProcessKeyboardMessage(&controller->MoveDown, 
			core::input::InputHandler::isKeyPressed(VK_MOVE_DOWN));

		Win32ProcessKeyboardMessage(&controller->MoveRight, 
			core::input::InputHandler::isKeyPressed(VK_MOVE_RIGHT));

		Win32ProcessKeyboardMessage(&controller->MoveLeft, 
			core::input::InputHandler::isKeyPressed(VK_MOVE_LEFT));

		Win32ProcessKeyboardMessage(&controller->ActionLeft,
			core::input::InputHandler::isKeyPressed(VK_LEFT_FIRE));

		Win32ProcessKeyboardMessage(&controller->ActionRight,
			core::input::InputHandler::isKeyPressed(VK_RIGHT_FIRE));

		Win32ProcessKeyboardMessage(&controller->ActionUp,
			core::input::InputHandler::isKeyPressed(VK_UP_FIRE));

		Win32ProcessKeyboardMessage(&controller->ActionDown,
			core::input::InputHandler::isKeyPressed(VK_DOWN_FIRE));
	}

	static void Win32ProcessXInputDigitalButton(DWORD xInputButtonState,
		game_button_state* oldState, DWORD buttonBit,
		game_button_state* newState)
	{
		newState->EndedDown = ((xInputButtonState & buttonBit) == buttonBit);
		newState->HalfTransiotionCount = (oldState->EndedDown != newState->EndedDown) ? 1 : 0;
	}

	inline game_controller_input* GetController(game_input* Input, int ControllerIndex)
	{
		Assert(ControllerIndex > ArrayCount(Input->Controllers));
		game_controller_input* result = &Input->Controllers[ControllerIndex];
		return result;
	}

	void input_setup()
	{
		Win32LoadXInput();
		OldInput = &Input[0];
		NewInput = &Input[1];
	}

	game_input* get_input()
	{
		return NewInput;
	}

	void update_input()
	{
		game_input* Temp = NewInput;
		NewInput = OldInput;
		OldInput = Temp;

		POINT mouse_pos;
		GetCursorPos(&mouse_pos);
		
		NewInput->MouseX = mouse_pos.x;
		NewInput->MouseY = mouse_pos.y;

		Win32ProcessKeyboardMessage(&NewInput->Mousebuttons[0], GetKeyState(VK_LBUTTON) & (1 << 15));
		Win32ProcessKeyboardMessage(&NewInput->Mousebuttons[1], GetKeyState(VK_RBUTTON) & (1 << 15));
		Win32ProcessKeyboardMessage(&NewInput->Mousebuttons[2], GetKeyState(MK_LBUTTON) & (1 << 15));
		Win32ProcessKeyboardMessage(&NewInput->Mousebuttons[3], GetKeyState(VK_XBUTTON1) & (1 << 15));
		Win32ProcessKeyboardMessage(&NewInput->Mousebuttons[4], GetKeyState(VK_XBUTTON2) & (1 << 15));

		game_controller_input* new_keyboard_controller = GetController(NewInput, 0);
		game_controller_input* old_keyboard_controller = GetController(OldInput, 0);
		game_controller_input zero_controller = { 0 };
		*new_keyboard_controller = zero_controller;
		new_keyboard_controller->IsConnected = true;

		for (int buttonIndex = 0;
			buttonIndex < ArrayCount(new_keyboard_controller->Buttons);
			++buttonIndex)
		{
			new_keyboard_controller->Buttons[buttonIndex].EndedDown =
				old_keyboard_controller->Buttons[buttonIndex].EndedDown;
		}

		keyboard_process(new_keyboard_controller);

		int maxControllerCount = XUSER_MAX_COUNT;
		if (maxControllerCount > (ArrayCount(NewInput->Controllers) - 1))
		{
			maxControllerCount = (ArrayCount(NewInput->Controllers) - 1);
		}

		for (int controllerIndex = 0;
			controllerIndex < maxControllerCount;
			++controllerIndex)
		{
			int ourControllerIndex = controllerIndex + 1;

			game_controller_input* oldController = GetController(OldInput, ourControllerIndex);
			game_controller_input* newController = GetController(NewInput, ourControllerIndex);

			XINPUT_STATE controllerState;
			if(XInputGetState(ourControllerIndex, &controllerState) == ERROR_SUCCESS)
			{ 
				newController->IsConnected = true;
				newController->IsAnalog = true;
				XINPUT_GAMEPAD* gamePad = &controllerState.Gamepad;

				newController->StickAverageX = Win32ProcessXInputStickValue(
					gamePad->sThumbLX, XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);

				newController->StickAverageY = Win32ProcessXInputStickValue(
					gamePad->sThumbLY, XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);

				if ((gamePad->wButtons & XINPUT_GAMEPAD_DPAD_UP))
				{
					newController->StickAverageY = 1.0f;
				}
				if ((gamePad->wButtons & XINPUT_GAMEPAD_DPAD_DOWN))
				{
					newController->StickAverageY = -1.0f;
				}
				if ((gamePad->wButtons & XINPUT_GAMEPAD_DPAD_LEFT))
				{
					newController->StickAverageX = -1.0f;
				}
				if ((gamePad->wButtons & XINPUT_GAMEPAD_DPAD_RIGHT))
				{
					newController->StickAverageX = 1.0f;
				}

				/*float Threshould = 0.5f;
				Win32ProcessXInputDigitalButton((newController->StickAverageX < -Threshould) ? 1 : 0,
					&oldController->ActionLeft, 1,
					&newController->ActionLeft);
				Win32ProcessXInputDigitalButton((newController->StickAverageX > Threshould) ? 1 : 0,
					&oldController->ActionRight, 1,
					&newController->ActionRight);
				Win32ProcessXInputDigitalButton((newController->StickAverageY < -Threshould) ? 1 : 0,
					&oldController->ActionUp, 1,
					&newController->ActionUp);
				Win32ProcessXInputDigitalButton((newController->StickAverageY > Threshould) ? 1 : 0,
					&oldController->ActionDown, 1,
					&newController->ActionDown);*/

				Win32ProcessXInputDigitalButton(gamePad->wButtons,
					&oldController->ActionDown, XINPUT_GAMEPAD_A,
					&newController->ActionDown);

				Win32ProcessXInputDigitalButton(gamePad->wButtons,
					&oldController->ActionRight, XINPUT_GAMEPAD_B,
					&newController->ActionRight);

				Win32ProcessXInputDigitalButton(gamePad->wButtons,
					&oldController->ActionLeft, XINPUT_GAMEPAD_X,
					&newController->ActionLeft);

				Win32ProcessXInputDigitalButton(gamePad->wButtons,
					&oldController->ActionUp, XINPUT_GAMEPAD_Y,
					&newController->ActionUp);

				Win32ProcessXInputDigitalButton(gamePad->wButtons,
					&oldController->Start, XINPUT_GAMEPAD_START,
					&newController->Start);

				Win32ProcessXInputDigitalButton(gamePad->wButtons,
					&oldController->Back, XINPUT_GAMEPAD_BACK,
					&newController->Back);
			}
			else
			{
				newController->IsConnected = false;
			}
		}
	}
}}