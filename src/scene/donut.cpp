#include "donut.h"

ENGINE_HEADER_BEGIN

donut::donut(Real major_radius, Real minor_radius, const Vec &position, const Mat &rotation)
    : Mesh(position, rotation), major_radius(major_radius), minor_radius(minor_radius) {}

RayHitInfo donut::hit_ray(const Ray &local_ray) const {
    Real step = 1;
    constexpr Real range_size = 10;
    Real min = sqr(minor_radius) - range_size;
    Real max = sqr(minor_radius) + range_size;
    for (Real time = 0; time < 100; time += step) {
        auto [x, y, z] = local_ray(time);
        Real projection_radius = sqrt(sqr(x) + sqr(y));
        Real sqr_distance = sqr(projection_radius - major_radius) + sqr(z);
        if (sqr_distance > min && sqr_distance < max) {
            return {1 / time, normalized({(projection_radius - major_radius) * x / projection_radius, (projection_radius - major_radius) * y / projection_radius, z})};
        }
    }
    return {0, 0}; // No hit.
}

ENGINE_HEADER_END
