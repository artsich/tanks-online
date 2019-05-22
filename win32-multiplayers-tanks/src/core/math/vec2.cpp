#include "vec2.h"
#include "geometryutils.h"

namespace math {

	vec2::vec2(float x, float y) {
		this->x = x;
		this->y = y;
	}

	vec2::vec2(const vec2& other) {
		this->x = other.x;
		this->y = other.y;
	}

	vec2::~vec2() { };

	vec2& vec2::add(const vec2& other) {
		x += other.x;
		y += other.y;
		return *this;
	}

	vec2& vec2::sub(const vec2& other) {
		x -= other.x;
		y -= other.y;
		return *this;
	}

	vec2& vec2::mult(const vec2& other) {
		x *= other.x;
		y *= other.y;
		return *this;
	}

	vec2& vec2::div(const vec2& other) {
		x /= other.x;
		y /= other.y;
		return *this;
	}

	vec2 operator + (vec2 left, const vec2& other) {
		return left.add(other);
	}

	vec2 operator - (vec2 left, const vec2& other) {
		return left.sub(other);
	}

	vec2 operator * (vec2 left, const vec2& other) {
		return left.mult(other);
	}

	vec2 operator / (vec2 left, const vec2& other) {
		return left.div(other);
	}

	vec2& vec2::operator+= (const vec2& other) {
		return add(other);
	}

	vec2& vec2::operator -= (const vec2& other) {
		return sub(other);
	}

	vec2& vec2::operator *= (const vec2& other) {
		return mult(other);
	}

	vec2& vec2::operator /= (const vec2& other) {
		return div(other);
	}

	bool vec2::operator == (const vec2& other) {
		bool result = false;
		if (x == other.x && y == other.y) {
			result = true;
		}
		return result;
	}

	bool vec2::operator != (const vec2& other) {
		bool result = false;
		if (!(*this == other)) {
			result = true;
		}
		return result;
	}

	vec2& vec2::add(const float& scalar) {
		x += scalar;
		y += scalar;
		return *this;
	}
	vec2& vec2::sub(const float& scalar) {
		x -= scalar;
		y -= scalar;
		return *this;
	}
	vec2& vec2::mult(const float& scalar) {
		x *= scalar;
		y *= scalar;
		return *this;
	}
	vec2& vec2::div(const float& scalar) {
		x /= scalar;
		y /= scalar;
		return *this;
	}

	vec2 operator+(vec2 left, const float& scalar) {
		return left.add(scalar);
	}

	vec2 operator-(vec2 left, const float& scalar) {
		return left.sub(scalar);
	}

	vec2 operator/(vec2 left, const float& scalar) {
		return left.div(scalar);
	}

	vec2 operator*(vec2 left, const float& scalar) {
		return left.mult(scalar);
	}

	vec2& vec2::operator+=(const float& scalar) {
		return add(scalar);
	}

	vec2& vec2::operator-=(const float& scalar) {
		return sub(scalar);
	}

	vec2& vec2::operator*=(const float& scalar) {
		return mult(scalar);
	}

	vec2& vec2::operator/=(const float& scalar) {
		return div(scalar);
	}

	void vec2::Normalize()
	{
		f32 L = Length();
		x /= L;
		y /= L;
	}

	f32 vec2::Length()
	{
		return std::sqrt(x*x + y*y);
	}

	void vec2::Rotate(f32 radian)
	{
		f32 NewX, NewY;
		NewX =  x * cosf(radian) - y * sinf(radian);
		NewY = -x * sinf(radian) - y * cosf(radian);

		x = NewX;
		y = NewY;
	}
}