#pragma once

#include "../core.h"
#include "../math/math.h"
#include "../window/Window.h"

namespace core { namespace graphics {

	struct simple_sprite
	{
		math::v2 pos;
		math::v2 size;
		u32 color;
	};

	struct texture {
		u32 width;
		u32 height;

		void* buffer;
	};

	struct sprite {
		math::vec2 pos;
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