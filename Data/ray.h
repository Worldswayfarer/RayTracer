#pragma once
#ifndef RAY_H
#define RAY_H

#include "vector3.h"

class ray {
public:
    ray() {}

    ray(const vector3& origin, const vector3& direction) : _origin(origin), _direction(direction) {}

    const point3& origin() const { return _origin; }
    const vector3& direction() const { return _direction; }

    point3 at(double t) const {
        return _origin + t * _direction;
    }

private:
    point3 _origin;
    vector3 _direction;
};

#endif