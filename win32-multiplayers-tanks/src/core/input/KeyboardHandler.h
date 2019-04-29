#pragma once

#include "IKeyListener.h"

namespace core { namespace input {

#define MAX_KEYS 256

	class InputHandler : public IKeyListener {
	private:
		static bool keys[];

	public:

		InputHandler();
		static bool isKeyPressed(int keyCode);
		void pressedKey(int keyCode) override;
		void releaseKey(int keyCode) override;
	};
}}