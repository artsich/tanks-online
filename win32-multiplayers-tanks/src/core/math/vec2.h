#pragma once
#include <iostream>
#include "../core.h"

namespace math {

	struct vec2 {

		f32 x, y;

		vec2() = default;
		vec2(const vec2& other);
		vec2(float x, float y);
		~vec2();
		
		vec2& add(const vec2& other);
		vec2& sub(const vec2& other);
		vec2& mult(const vec2& other);
		vec2& div(const vec2& other);

		friend vec2 operator+(vec2 left, const vec2& right);
		friend vec2 operator-(vec2 left, const vec2& right);
		friend vec2 operator/(vec2 left, const vec2& right);
		friend vec2 operator*(vec2 left, const vec2& right);

		vec2& operator+=(const vec2& right);
		vec2& operator-=(const vec2& right);
		vec2& operator*=(const vec2& right);
		vec2& operator/=(const vec2& right);


		vec2& add(const float& scalar);
		vec2& sub(const float& scalar);
		vec2& mult(const float& scalar);
		vec2& div(const float& scalar);

		friend vec2 operator+(vec2 left, const float& scalar);
		friend vec2 operator-(vec2 left, const float& scalar);
		friend vec2 operator/(vec2 left, const float& scalar);
		friend vec2 operator*(vec2 left, const float& scalar);

		vec2& operator+=(const float& scalar);
		vec2& operator-=(const float& scalar);
		vec2& operator*=(const float& scalar);
		vec2& operator/=(const float& scalar);

		bool operator != (const vec2& other);
		bool operator == (const vec2& other);

		friend std::ostream& operator << (std::ostream& stream, const vec2& other);
	};

	typedef vec2 v2;
}