#pragma once
#include "../Data/vector3.h"
#include <limits>

struct AABB 
{
	point3 _min;
	point3 _max;

	AABB() {
		for (int i = 0; i < 3; ++i) {
			_min[i] = std::numeric_limits<float>::infinity();
			_max[i] = -std::numeric_limits<float>::infinity();
		}
	};

	AABB(const point3& _min, const point3& _max)
		: _min(_min), _max(_max)
	{
	}
};