#pragma once

#include "IKeyListener.h"

namespace core { namespace input {

#define MAX_KEYS 256

	class InputHandler : public IKeyListener {
	private:
		static bool keys[];

	public:
		static bool isKeyPressed(int keyCode) {
			if (keyCode > MAX_KEYS) {
				return false;
			}
			return keys[keyCode];
		}

		void pressedKey(int keyCode) override {
			if (keyCode < MAX_KEYS) {
				keys[keyCode] = true;
			}
		}

		void releaseKey(int keyCode) override {
			keys[keyCode] = false;
		}
	};

	bool InputHandler::keys[MAX_KEYS];
}}