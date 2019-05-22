#include "geometryutils.h"
using namespace math;

bool RayLineIntersection(v2& p1, v2& p2, v2& p3, v2& p4, v2& intersectionPoint)
{
	f32 x1 = p1.x;
	f32 y1 = p1.y;
	f32 x2 = p2.x;
	f32 y2 = p2.y;
	
	f32 x3 = p3.x;
	f32 y3 = p3.y;
	f32 x4 = p4.x;
	f32 y4 = p4.y;
	
	f32 denominator = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);

	if (denominator == 0)
	{
		return false;
	}

	f32 t = ((x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4)) / denominator;
	f32 u = -((x1 - x2) * (y1 - y3) - (y1 - y2) * (x1 - x3)) / denominator;

	if (t > 0.0 && t < 1.0f && u > 0.0)
	{
		intersectionPoint.x = (x1 + t * (x2 - x1));
		intersectionPoint.y = (y1 + t * (y2 - y1));
		return true;
	}
	else
	{
		return false;
	}
}
