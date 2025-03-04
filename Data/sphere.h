#pragma once
#include "vector3.h"
#include "ray.h"

class sphere 
{
public:
	double ray_sphere_intersetion(const ray& raymond);
	sphere(point3 center, double radius) : center(center), radius(radius) {}
private:
	point3 center;
	double radius;
};