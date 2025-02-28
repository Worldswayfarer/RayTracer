#include "Construct_BVH.h"
#include <vector>
#include <algorithm>
#include <limits>
#include <cmath>


const int number_of_buckets = 2;

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
    for (const triangle3 obj : *primitives) {
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
    size_t bestSplit = 1;
    int bestAxis = 0;
    
    size_t primitives_per_bucket = primitives->size() / number_of_buckets;

    std::vector<triangle3>* left;
    std::vector<triangle3>* right;

    if (primitives->size() == 2) {
        node->left_child = construct_node(node, new std::vector<triangle3>{ primitives->at(0) });
        node->right_child = construct_node(node, new std::vector<triangle3>{ primitives->at(1) });
        return node;
    }

    
    for (int axis = 0; axis < 3; axis++) {
        std::sort(primitives->begin(), primitives->end(), [axis](const triangle3& a, const triangle3& b) {
            return (axis == 0 ? a.center().x() : (axis == 1 ? a.center().y() : a.center().z())) <
                (axis == 0 ? b.center().x() : (axis == 1 ? b.center().y() : b.center().z()));
            });
        for (int bucket = 1; bucket < number_of_buckets; bucket++) {
            left = new std::vector<triangle3>(primitives->begin(), primitives->begin() + bucket * primitives_per_bucket);
            right = new std::vector<triangle3>(primitives->begin() + bucket * primitives_per_bucket, primitives->end());

            AABB* leftBox = construct_AABB(left);
            AABB* rightBox = construct_AABB(right);
            float sahCost = 1 + (compute_surface_area(leftBox) )/ (compute_surface_area(parent_AABB))  * left->size() +
                 (compute_surface_area(rightBox) ) /(compute_surface_area(parent_AABB))  * right->size();

            if (sahCost < bestCost) {
                bestCost = sahCost;
                bestSplit = bucket;
                bestAxis = axis;
            }
        }
        
    }


    std::sort(primitives->begin(), primitives->end(), [bestAxis](const triangle3& a, const triangle3& b) {
        return (bestAxis == 0 ? a.center().x() : (bestAxis == 1 ? a.center().y() : a.center().z())) <
            (bestAxis == 0 ? b.center().x() : (bestAxis == 1 ? b.center().y() : b.center().z()));
        });
    left = new std::vector<triangle3>(primitives->begin(), primitives->begin() + bestSplit * primitives_per_bucket);
    right = new std::vector<triangle3>(primitives->begin() + bestSplit * primitives_per_bucket, primitives->end());

    node->left_child = construct_node(node, left);
    node->right_child = construct_node(node, right);
    return node;
}

BVHNode* construct_BVH(std::vector<triangle3>* primitives)
{
    return construct_node(nullptr, primitives);
}


