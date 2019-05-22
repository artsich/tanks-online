#pragma once

#include "math.h"
using namespace math;

#define PI 3.1415926

//p1 - ray.P
//p2 - ray.P + ray.D
bool RayLineIntersection(v2& p1, v2& p2, v2& p3, v2& p4, v2& inPoint);

inline f32 ToRadian(f32 degree)
{
	return degree * PI / 180.0f;
}