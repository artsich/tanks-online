#pragma once

#include "../core.h"
#include "../math/vec2.h"
#include "../window/Window.h"

namespace core { namespace graphics {

	struct simple_sprite
	{
		core::math::vec2 pos;
		core::math::vec2 size;
		uint32_t color;
	};

	struct texture {
		uint32_t width;
		uint32_t height;

		void* buffer;
	};

	struct sprite {
		core::math::vec2 pos;
		texture texture;
	};

	class Rasterizer
	{
	private:
		core::screen_buffer* buffer;

	public:
		Rasterizer(core::screen_buffer* buffer);

		void draw_rect(sprite* sprite);
		void draw_rect(simple_sprite* sprite);
	};
} }