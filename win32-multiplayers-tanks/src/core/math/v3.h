#pragma once

#include "../core.h"

namespace math
{
	union v3
	{
		struct
		{
			f32 x, y, z;
		};

		struct
		{
			f32 r, g, b;
		};
	};

	v3 operator + (v3& A, v3& B); 
	v3 operator - (v3& A, v3& B);
	v3 operator * (v3& A, v3& B);
	v3 operator / (v3& A, v3& B);

	v3& operator += (v3& A, v3 B);	
	v3& operator -= (v3& A, v3 B);	
	v3& operator *= (v3& A, v3 B);	
	v3& operator /= (v3& A, v3 B);

	v3 operator / (v3& A, f32 b);
	v3 operator * (v3& A, f32 b);
	v3 operator + (v3& A, f32 b);
	v3 operator - (v3& A, f32 b);

	v3& operator /= (v3& A, f32 b);
	v3& operator += (v3& A, f32 b);
	v3& operator -= (v3& A, f32 b);
	v3& operator *= (v3& A, f32 b);
}