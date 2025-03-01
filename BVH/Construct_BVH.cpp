#include "Construct_BVH.h"
#include <vector>
#include <algorithm>
#include <limits>
#include <cmath>


const int number_of_buckets = 4;

bool compareX(triangle3& a, triangle3& b)
{
    return a.center().x() < b.center().x();
}
bool compareY(triangle3& a, triangle3& b)
{
    return a.center().y() < b.center().y();
}
bool compareZ(triangle3& a, triangle3& b)
{
    return a.center().z() < b.center().z();
}

AABB* construct_AABB(const std::vector<triangle3>* primitives) {
    vector3 max = { std::numeric_limits<float>::lowest(), std::numeric_limits<float>::lowest(), std::numeric_limits<float>::lowest() };
    vector3 min = { std::numeric_limits<float>::max(), std::numeric_limits<float>::max(), std::numeric_limits<float>::max() };
    for (const triangle3 &obj : *primitives) {
        min = minimum(min, obj.a());
        max = maximum(max, obj.a());
        min = minimum(min, obj.b());
        max = maximum(max, obj.b());
        min = minimum(min, obj.c());
        max = maximum(max, obj.c());
    }
    AABB*box = new AABB(min, max);
    return box;
}


float compute_surface_area(const AABB* box) {
    vector3 d = { box->_max.x() - box->_min.x(), box->_max.y() - box->_min.y(), box->_max.z() - box->_min.z() };
    return 2 * (d.x() * d.y() + d.y() * d.z() + d.z() * d.x());
}

AABB* expand_AABB(AABB* target, AABB* other) {
    target->_min = minimum(target->_min, other -> _min);
    target->_max = maximum(target->_max, other->_max);
    return target;
}

struct Bucket {
    AABB bounds;
    int count = 0;

    Bucket() = default;
};

bool is_valid_AABB(AABB target) {
    return (target._min[0] <= target._max[0]) && (target._min[1] <= target._max[1]) && (target._min[2] <= target._max[2]);
}



BVHNode* construct_node(BVHNode* parent, std::vector<triangle3>* primitives)
{
    BVHNode* node = new BVHNode();

    

    AABB* parent_AABB;
    if (!parent) {
        parent_AABB = construct_AABB(primitives);
    }
    else {
        parent_AABB = parent->box;
    }
    node->box = construct_AABB(primitives);
 
    
    if (primitives->size() <= 1) {
        if (primitives->size() == 1)
        {
            node->primitive = &primitives->at(0);
            return node;
        }
        return NULL;
    }
    float bestCost = std::numeric_limits<float>::infinity();
    float bestSplit = 0;
    int bestAxis = -1;
    

    std::vector<triangle3>* left_prim = new std::vector<triangle3>;
    std::vector<triangle3>* right_prim = new std::vector<triangle3>;

    for (int axis = 0; axis < 3; axis++) {
       
        float min_axis = parent_AABB->_min[axis], max_axis = parent_AABB->_max[axis];
        if (max_axis == min_axis) continue; // Skip degenerate cases

        // Initialize buckets
        std::vector<Bucket> buckets(number_of_buckets);
        float bucket_size = (max_axis - min_axis) / number_of_buckets;

        // Assign primitives to buckets
        for (const auto& p : *primitives) {
            int b = std::min(number_of_buckets - 1, int((p.center()[axis] - min_axis) / bucket_size));
            expand_AABB(&buckets[b].bounds, parent_AABB);
            buckets[b].count++;
        }
        
        AABB left;
        AABB right;
        int left_count = 0, right_count = primitives->size();
        for (int bucket = 0; bucket < number_of_buckets; bucket++) {
            
            expand_AABB(&left, &buckets[bucket].bounds);
            left_count += buckets[bucket].count;
            right_count -= buckets[bucket].count;

            //if (left_count == 0 || right_count == 0) continue;

            right = AABB();
            for (int j = bucket + 1; j < number_of_buckets; ++j) {
                expand_AABB(&right, &buckets[bucket].bounds);
            }

            if (!is_valid_AABB(left) or !is_valid_AABB(right)){
                continue;
            }

            float sahCost = 1 + (compute_surface_area(&left) )/ (compute_surface_area(parent_AABB))  * left_count +
                 (compute_surface_area(&right) ) /(compute_surface_area(parent_AABB))  * right_count;

            float split_position = min_axis + (bucket + 1) * bucket_size;
            if (sahCost < bestCost) {
                bestCost = sahCost;
                bestSplit = split_position;
                bestAxis = axis;
            }
        }
        
    }

    
    for (const auto& p : *primitives) {
        if (p.center()[bestAxis] < bestSplit) {
            left_prim->push_back(p);  
        }
        else {
            right_prim->push_back(p);
        }
    }
    if (left_prim->size() == 0 || right_prim->size() == 0)
    {
        left_prim = new std::vector<triangle3>(primitives->begin(), primitives->begin() + primitives->size() / 2);
        right_prim = new std::vector<triangle3>(primitives->begin() + primitives->size() / 2, primitives->end());
    }
    node->left_child = construct_node(node, left_prim);
    node->right_child = construct_node(node, right_prim);
    return node;
}

BVHNode* construct_BVH(std::vector<triangle3>* primitives)
{
    return construct_node(nullptr, primitives);
}


