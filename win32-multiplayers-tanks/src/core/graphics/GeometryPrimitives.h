#pragma once
#include "../math/math.h"

namespace core { namespace graphics {

#define WHITE	0x0
#define RED		0xFF0000
#define GREEN	0x00FF00
#define BLUE	0x0000FF

	struct simple_sprite
	{
		math::v2 size;
		u32 color;
	};

	struct texture {
		u32 width;
		u32 height;

		void* buffer;
	};

	struct sprite {
		math::v2 pos;
		texture texture;
	};
} }