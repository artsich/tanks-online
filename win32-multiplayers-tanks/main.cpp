#include <Windows.h>
#include <iostream>
#include <string>
#include "src/core.h"
#include "src/imageloaders/loadbmp.h"
#include "src/utils/Timer.h"
#include "src/window/Window.h"

#define TEST_IMAGE_FILE "C:\\Users\\artyo\\source\\repos\\multiplayer-tanks\\Debug\\image.bmp"
#define TEST_TEXT_FILE "C:\\Users\\artyo\\source\\repos\\multiplayer-tanks\\Debug\\text.txt"

namespace core { namespace graphics {
	struct rectangle
	{
		uint32_t x;
		uint32_t y;
		uint32_t width;
		uint32_t height;
	};

	class Rasterization
	{
	private:
		core::window::screen_buffer* buffer;

	public:
		Rasterization(core::window::screen_buffer* buffer) : 
			buffer(buffer) 
		{}

		void draw_rect(rectangle rect, uint32_t color)
		{
			uint32_t* pixels = ((uint32_t*)buffer->Memory);
			if (!pixels) return;

			for (int y = rect.y; y < rect.height; ++y)
			{
				for (int x = rect.x; x < rect.width; ++x)
				{
					pixels[x + y * buffer->Width] = color;
				}
			}
		}
	};
}}

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPTSTR pCmdLine, int nCmdShow)
{
#pragma region Setup
	core::window::setting_window setting;
	setting.width = 800;
	setting.height = 600;
	setting.title = "World of tanks online";
	setting.HInstance = hInstance;
#pragma endregion

	core::window::Window window(&setting);
	core::window::screen_buffer* buffer = window.get_back_buffer();
	core::graphics::Rasterization resterizer(buffer);

	core::Timer timer;
	float time = 0.0;
	UINT64 frames = 0;
	UINT64 updates = 0;
	float lastTime = timer.elapsed();
	float delta = 0.0f;
	float framePerSecond = 1.0f / 60.0f;

	while (window.isClose())
	{
		float nowTime = timer.elapsed();
		delta += nowTime - lastTime;
		lastTime = nowTime;

		if (delta > framePerSecond)
		{
			delta = 0;
			updates++;
			window.processMessage();
		}

		window.clear();

		resterizer.draw_rect({ 10, 10, 300, 600 }, 255 << 16 | 255 << 8);
		window.render();
		frames++;

		if (timer.elapsed() - time > 1.0f)
		{
#if FPS_DEBUG
			OutputDebugString((std::to_string(frames) + " fps : " + std::to_string(updates) + " updates\n").c_str());
#endif
			time += 1.0f;
			updates = frames = 0;
		}
	}

	return 0;
}