#pragma once

#include "Window.h"
#include <vector>

namespace core { namespace window {

	class WindowManager {
	private:
		std::vector<Window*> list;

		WindowManager() {}
		~WindowManager() {}

		WindowManager(WindowManager const&) = delete;
		WindowManager& operator=(WindowManager const&) = delete;

	public:
		static WindowManager& getInstance();
		void add_window(core::window::Window* window);
		void close_window(const HWND& window);
	};
}}