#include "Rasterizer.h"

namespace core { namespace graphics {

	Rasterizer::Rasterizer(core::screen_buffer* buffer) :
		buffer(buffer)
	{}

	void Rasterizer::draw_rect(sprite* sprite)
	{
		uint32_t* pixels = ((uint32_t*)buffer->Memory);
		uint32_t* texture = (uint32_t*)sprite->Texture.buffer;

		if (!pixels || !texture)
		{
			return;
		}

		//uint32_t tx = 0, twidth = sprite->texture.width,
		//	ty = 0, theight = sprite->texture.height;

		int32_t xmin, xmax, ymin, ymax;
		xmin = sprite->pos.x;
		xmax = xmin + sprite->Texture.width;
		ymin = sprite->pos.y;
		ymax = ymin + sprite->Texture.height;

		if (xmin < 0)
		{
			xmin = 0;
		}
		if (ymin < 0)
		{
			ymin = 0;
		}
		if (xmax > buffer->Width)
		{
			xmax = buffer->Width;
		}
		if (ymax > buffer->Height)
		{
			ymax = buffer->Height;
		}

		for (uint32_t y = ymin; y < ymax; ++y)
		{
			uint32_t* buffer_row = (pixels + xmin + y * buffer->Width);
			for (uint32_t x = xmin; x < xmax; ++x)
			{
				*buffer_row++ = *texture++;
			}
		}
	}

	void Rasterizer::draw_rect(math::v2 pos, simple_sprite* sprite)
	{
		int32_t xmin, xmax, ymin, ymax;
		xmin = pos.x;
		xmax = xmin + sprite->size.x;
		ymin = pos.y;
		ymax = ymin + sprite->size.y;

		if (xmin < 0)
		{
			xmin = 0;
		}
		if (ymin < 0)
		{
			ymin = 0;
		}
		if (xmax > buffer->Width)
		{
			xmax = buffer->Width;
		}
		if (ymax > buffer->Height)
		{
			ymax = buffer->Height;
		}

		uint32_t* pixels = ((uint32_t*)buffer->Memory);
		if (!pixels) return;

		for (int y = ymin; y < ymax; ++y)
		{
			uint32_t* buffer_row = (pixels + xmin + y * buffer->Width);
			for (int x = xmin; x < xmax; ++x)
			{
				*buffer_row++ = sprite->color;
			}
		}
	}

	//Refactor method
	void Rasterizer::DrawLine(math::v2 p1, math::v2 p2, u32 color) 
	{	
		//p1 = toViewPort(p1);
		//p2 = toViewPort(p2);

		bool isSteep = LineIsSteep(p1, p2);

		if (isSteep) {
			std::swap(p1.x, p2.y);
			std::swap(p1.y, p2.x);
		}

		if (p1.x > p2.x) {
			std::swap(p1, p2);
		}

		int dx = p2.x - p1.x;
		int dy = p2.y - p1.y;
		int derror = std::abs(dy) * 2;
		int error = 0;
		int y = p1.y;
		int step = (p2.y > p1.y) ? 1 : -1;

		for (int x = p1.x; x < p2.x; ++x) {
			if (isSteep) {
				DrawPixel(y, x, color);
			}
			else {
				DrawPixel(x, y, color);
			}
			error += derror;
			if (error >= dx * 2) {
				y += step;
				error -= dx * 2;
			}
		}
	}

	inline void Rasterizer::DrawPixel(int x1, int y1, int color)
	{
		if (x1 >= 0 && x1 < buffer->Width &&
			y1 >= 0 && y1 < buffer->Height)
		{
			if (buffer->Memory)
			{
				((i32*)buffer->Memory)[x1 + y1 * buffer->Width] = color;
			}
		}
	}

	inline bool Rasterizer::LineIsSteep(math::v2& p1, math::v2& p2) {
		return std::abs(p2.x - p1.x) < std::abs(p2.y - p1.y);
	}

	inline void ToViewPort(f32& X, f32& Y, f32 W, f32 H)
	{
		X = W / 2 * (1 + X);
		Y = H / 2 * (1 + Y);
	}

	inline void FromViewPort(f32& X, f32& Y, f32 W, f32 H)
	{
		X = (2 * (X*W / 2)) / W;
		Y = (2 * (Y*H / 2)) / H;
	}
}}