#include "closest_intersection.h"
#include "global_values.h"
#include "BVH/BoundingVolumeTree.h"

Intersection* get_closest_intersection(size_t triangles_size, std::vector<triangle3>* triangles, ray& raymond)
{
    
    Intersection* closest_intersection = nullptr;
    for (int n = 0; n < triangles_size; n++)
    {
        //closest_intersection points to intersection, but the intersection gets rewritten every time
        Intersection* intersection = ray_triangle_intersection(&(*triangles)[n], raymond);
        if (!intersection)
        {
            continue;
        }


        if (!closest_intersection)
        {
            closest_intersection = intersection;
            continue;
        }

        //determine which of the 2 points is closer to the image
        if ((intersection->_intersection_point - raymond.origin()).length() + _epsilon
            < (closest_intersection->_intersection_point - raymond.origin()).length())
        {
            closest_intersection = intersection;
        }
    }
    return closest_intersection;
}


Intersection* get_BVH_closest_intersection(BVHNode* current_node, ray& raymond)
{
    if (current_node->primitive != nullptr)
    {
        return ray_triangle_intersection(current_node->primitive, raymond);
    }

    double left_t = ray_aabb_intersection(current_node->left_child->box, raymond);
    double right_t = ray_aabb_intersection(current_node->right_child->box, raymond);


    Intersection* left_intersection = nullptr;
    Intersection* right_intersection = nullptr;
    if(left_t != 0 and left_t <= right_t)
    {
        left_intersection = get_BVH_closest_intersection(current_node->left_child, raymond);
    }
    if (left_intersection != nullptr)
    {
        return left_intersection;
    }
    if(right_t != 0)
    { 
        return right_intersection = get_BVH_closest_intersection(current_node->right_child, raymond);
    }
    return nullptr;
}