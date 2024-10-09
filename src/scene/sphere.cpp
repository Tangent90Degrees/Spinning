#include "sphere.h"

ENGINE_HEADER_BEGIN

sphere::sphere(real radius, const vec &position, const mat &rotation)
    : mesh(position, rotation), radius(radius) {}

ray_hit_info sphere::hit_ray(const ray &local_ray) const {
    real a = sqr_norm(local_ray.direction);
    real b = 2 * dot(local_ray.direction, local_ray.origin);
    real c = sqr_norm(local_ray.origin) - sqr(radius);

    real discriminant = sqr(b) - 4 * a * c;

    if (discriminant < 0)
        return {0, 0};

    real sqrt_discriminant = sqrt(discriminant);
    real time = (-b - sqrt_discriminant) / (2 * a);

    if (time < 0) {
        time = (-b + sqrt_discriminant) / (2 * a);
        if (time < 0)
            return {0, 0};
    }

    return {1 / time, normalized(local_ray(time))};
}

ENGINE_HEADER_END
