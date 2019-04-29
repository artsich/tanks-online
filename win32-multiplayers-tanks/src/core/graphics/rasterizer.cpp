#include "Rasterizer.h"

namespace core { namespace graphics {

	Rasterizer::Rasterizer(core::screen_buffer* buffer) :
		buffer(buffer)
	{}

	void Rasterizer::draw_rect(sprite* sprite)
	{
		uint32_t* pixels = ((uint32_t*)buffer->Memory);
		uint32_t* texture = (uint32_t*)sprite->texture.buffer;

		if (!pixels || !texture)
		{
			return;
		}

		//uint32_t tx = 0, twidth = sprite->texture.width,
		//	ty = 0, theight = sprite->texture.height;

		int32_t xmin, xmax, ymin, ymax;
		xmin = sprite->pos.x;
		xmax = xmin + sprite->texture.width;
		ymin = sprite->pos.y;
		ymax = ymin + sprite->texture.height;

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

	void Rasterizer::draw_rect(simple_sprite* sprite)
	{
		int32_t xmin, xmax, ymin, ymax;
		xmin = sprite->pos.x;
		xmax = xmin + sprite->size.x;
		ymin = sprite->pos.y;
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
}}