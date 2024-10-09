#include "donut.h"

ENGINE_HEADER_BEGIN

donut::donut(real major_radius, real minor_radius, const vec &position, const mat &rotation)
    : mesh(position, rotation), major_radius(major_radius), minor_radius(minor_radius) {}

ray_hit_info donut::hit_ray(const ray &local_ray) const {
    real step = 1;
    constexpr real range_size = 10;
    real min = sqr(minor_radius) - range_size;
    real max = sqr(minor_radius) + range_size;
    for (real time = 0; time < 100; time += step) {
        auto [x, y, z] = local_ray(time);
        real projection_radius = sqrt(sqr(x) + sqr(y));
        real sqr_distance = sqr(projection_radius - major_radius) + sqr(z);
        if (sqr_distance > min && sqr_distance < max) {
            return {1 / time, normalized({(projection_radius - major_radius) * x / projection_radius, (projection_radius - major_radius) * y / projection_radius, z})};
        }
    }
    return {0, 0}; // No hit.
}

ENGINE_HEADER_END
