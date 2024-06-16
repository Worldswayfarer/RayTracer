#pragma once
#include "vector3.h"
#include "ray.h"

class sphere 
{
public:
	double ray_sphere_intersetion(const ray& raymond);

private:
	point3 center;
	double radius;
};