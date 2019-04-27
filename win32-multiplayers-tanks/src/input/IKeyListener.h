#pragma once

namespace core { namespace input {

	class IKeyListener {

	public:
		virtual void pressedKey(int keyCode) = 0;
		virtual void releaseKey(int keyCode) = 0;
	};

}}