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
		void draw_rect(math::v2 pos, simple_sprite* sprite);		
		
		void DrawLine(math::v2 p1, math::v2 p2, u32 color);

	private:
		bool Rasterizer::LineIsSteep(math::v2& p1, math::v2& p2);

		void DrawPixel(int x1, int y1, int color);
	};

	void ToViewPort(f32& X, f32& Y, f32 W, f32 H);
	void FromViewPort(f32& X, f32& Y, f32 W, f32 H);

} }