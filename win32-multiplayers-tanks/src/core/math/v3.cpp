#include "v3.h"

namespace math
{

	v3 operator + (v3& A, v3& B)
	{
		v3 result;
		result.x = A.x + B.x;
		result.y = A.y + B.y;
		result.z = A.z + B.z;
		return result;
	}

	v3& operator += (v3& A, v3 B)
	{
		A = A + B;
		return A;
	}

	v3 operator - (v3& A, v3& B)
	{
		v3 result;
		result.x = A.x - B.x;
		result.y = A.y - B.y;
		result.z = A.z - B.z;
		return result;
	}

	v3& operator -= (v3& A, v3 B)
	{
		A = A - B;
		return A;
	}

	v3 operator * (v3& A, v3& B)
	{
		v3 result;
		result.x = A.x * B.x;
		result.y = A.y * B.y;
		result.z = A.z * B.z;
		return result;
	}

	v3& operator *= (v3& A, v3 B)
	{
		A = A * B;
		return A;
	}

	v3 operator / (v3& A, v3& B)
	{
		v3 result;
		result.x = A.x / B.x;
		result.y = A.y / B.y;
		result.z = A.z / B.z;
		return result;
	}

	v3& operator /= (v3& A, v3 B)
	{
		A = A / B;
		return A;
	}

	v3 operator / (v3& A, f32 b)
	{
		v3 result;
		result.x = A.x / b;
		result.y = A.y / b;
		result.z = A.z / b;
		return result;
	}

	v3& operator /= (v3& A, f32 b)
	{
		A = A / b;
		return A;
	}

	v3 operator * (v3& A, f32 b)
	{
		v3 result;
		result.x = A.x * b;
		result.y = A.y * b;
		result.z = A.z * b;
		return result;
	}

	v3& operator *= (v3& A, f32 b)
	{
		A = A * b;
		return A;
	}

	v3 operator + (v3& A, f32 b)
	{
		v3 result;
		result.x = A.x + b;
		result.y = A.y + b;
		result.z = A.z + b;
		return result;
	}

	v3& operator += (v3& A, f32 b)
	{
		A = A + b;
		return A;
	}

	v3 operator - (v3& A, f32 b)
	{
		v3 result;
		result.x = A.x - b;
		result.y = A.y - b;
		result.z = A.z - b;
		return result;

	}

	v3& operator -= (v3& A, f32 b)
	{
		A = A - b;
		return A;
	}
}