#pragma once

#include "../core.h"
#include "../window/Window.h"
#include "./GeometryPrimitives.h"

namespace core { namespace graphics {

	class Rasterizer
	{
	public:
		core::screen_buffer* buffer;

	public:
		Rasterizer(core::screen_buffer* buffer);

		void draw_rect(sprite* sprite);
		void Rasterizer::draw_rect(math::v2 pos, simple_sprite* sprite);
	};
} }