#include "sphere.h"

ENGINE_HEADER_BEGIN

sphere::sphere(Real radius, const Vec &position, const Mat &rotation)
    : Mesh(position, rotation), radius(radius) {}

RayHitInfo sphere::hit_ray(const Ray &local_ray) const {
    Real a = sqr_norm(local_ray.direction);
    Real b = 2 * dot(local_ray.direction, local_ray.origin);
    Real c = sqr_norm(local_ray.origin) - sqr(radius);

    Real discriminant = sqr(b) - 4 * a * c;

    if (discriminant < 0)
        return {0, 0};

    Real sqrt_discriminant = sqrt(discriminant);
    Real time = (-b - sqrt_discriminant) / (2 * a);

    if (time < 0) {
        time = (-b + sqrt_discriminant) / (2 * a);
        if (time < 0)
            return {0, 0};
    }

    return {1 / time, normalized(local_ray(time))};
}

ENGINE_HEADER_END
