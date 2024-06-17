#include "closest_intersection.h"


Intersection* get_closest_intersection(double focal_length, point3 pixel_point,
    size_t triangles_size, triangle3* triangles, ray& raymond)
{
    Intersection* closest_intersection = NULL;
    for (int n = 0; n < triangles_size; n++)
    {
        //closest_intersection points to intersection, but the intersection gets rewritten every time
        Intersection* intersection = ray_triangle_intersection(&triangles[n], raymond);
        if (!intersection)
        {
            continue;
        }
        double ray_t = intersection->_ray_t;
        if (ray_t < 0) { continue; }

        vector3 distance_ray_point = raymond.direction() * ray_t;
        // intersection is behind the image
        if (distance_ray_point.length() < focal_length) { continue; }


        if (!closest_intersection)
        {
            closest_intersection = intersection;
            continue;
        }

        //determine which of the 2 points is closer to the image
        if ((intersection->_intersection_point - pixel_point).length() 
            < (closest_intersection->_intersection_point - pixel_point).length())
        {
            closest_intersection = intersection;
        }
    }
    return closest_intersection;
}