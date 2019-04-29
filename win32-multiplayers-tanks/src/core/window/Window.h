#pragma once

#include <Windows.h>
#include "../input/IKeyListener.h"
#include "../core.h"

namespace core { namespace window {

#define CLEAR_COLOR 0x00FFFFFF

	struct window_dimension {
		int widht, height;
	};

	struct setting_window {
		const char* title;
		const char* windowClassName;

		int width;
		int height;
		int windowWidth;
		int windowHeight;

		HINSTANCE hInstance;
	};

	class Window {
	private:
		screen_buffer screenBuffer;
		BITMAPINFO bitmapInfo;

		HWND HandleWindow;
		WNDCLASS WindowClass;
		BOOLEAN Running;
		const setting_window* setting;
		core::input::IKeyListener* keyListener;

	public:
		Window(const setting_window* setting);
		~Window();

		void render();
		void processMessage();
		void clear();
		void close();

		bool isClose() const { return Running; }

		void set_key_listener(core::input::IKeyListener* keyListener);

		const HWND& get_hwnd() const { return HandleWindow; }
		screen_buffer* get_back_buffer() { return &screenBuffer; }

	private:
		void ResizeSection(int width, int height);
		window_dimension GetClientRectangle();
		void InitWindow(const setting_window* setting);

		static LRESULT CALLBACK Win32WindowCallback(HWND Window, UINT Message, WPARAM WParam, LPARAM LParam);
	};
}}