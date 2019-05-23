#pragma once
#include "../math/math.h"

namespace core { namespace graphics {

#define WHITE	0x000000
#define RED		0xFF0000
#define GREEN	0x00FF00
#define BLUE	0x0000FF

	struct ray
	{
		v2 P;
		v2 D;

		void LookAt(f32 x, f32 y)
		{
			D.x = x - P.x;
			D.y = y - P.y;
			D.Normalize();
		}

		bool IsIntersection(v2& p1, v2& p2, v2& inPoint)
		{
			return RayLineIntersection(p1, p2, P, P + D, inPoint);
		}
	};

	struct line
	{
		v2 P1, P2;
	};

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
		texture Texture;
	};
} }