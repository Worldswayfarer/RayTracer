#include "sphere.h"

double sphere::ray_sphere_intersetion(const ray& raymond)
{
    vector3 oc = center - raymond.origin();
    double a = dot_product(raymond.direction(), raymond.direction());
    double b = -2.0 * dot_product(raymond.direction(), oc);
    double c = dot_product(oc, oc) - radius * radius;
    double discriminant = b * b - 4 * a * c;

    if (discriminant < 0) {
        return -1.0;
    }
    return (-b + sqrt(discriminant)) / (2.0 * a);
}
