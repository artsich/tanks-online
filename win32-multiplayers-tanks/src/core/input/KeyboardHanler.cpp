#include "KeyboardHandler.h"

namespace core { namespace input {

	InputHandler::InputHandler() 
	{
	}

	bool InputHandler::isKeyPressed(int keyCode) 
	{
		if (keyCode > MAX_KEYS) {
			return false;
		}
		return keys[keyCode];
	}

	void InputHandler::pressedKey(int keyCode) 
	{
		if (keyCode < MAX_KEYS) 
		{
			keys[keyCode] = true;
		}
	}

	void InputHandler::releaseKey(int keyCode) 
	{
		if (keyCode < MAX_KEYS) 
		{
			keys[keyCode] = false;
		}
	}

	bool InputHandler::keys[MAX_KEYS];
} }