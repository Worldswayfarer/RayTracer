#pragma once
#include "../Data/vector3.h"

struct AABB 
{
	point3 _min;
	point3 _max;

	AABB() = default;

	AABB(const point3& _min, const point3& _max)
		: _min(_min), _max(_max)
	{
	}
};