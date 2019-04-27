#pragma once

#include <Windows.h>
#include "../input/IKeyListener.h"

namespace core { namespace window {

#define CLEAR_COLOR 0xFF00FF

	struct screen_buffer {
		BITMAPINFO Info;
		int Width;
		int Height;
		int BytesPerPixel;
		int Pitch;
		void* Memory;
	};

	struct window_dimension {
		int widht, height;
	};

	struct setting_window {
		const char* title;
		int width;
		int height;
		HINSTANCE HInstance;
	};

	class Window {
	private:
		screen_buffer screenBuffer;
		HWND HandleWindow;
		WNDCLASS WindowClass;
		BOOLEAN Running;

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
		void ResizeDIBSection(int width, int height);
		window_dimension GetClientRectangle();
		void InitWindow(HINSTANCE HInstance, const char* title, int width, int height);
		static LRESULT CALLBACK Win32WindowCallback(HWND Window, UINT Message, WPARAM WParam, LPARAM LParam);
	};
}}