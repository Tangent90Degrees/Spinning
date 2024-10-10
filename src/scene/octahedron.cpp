#include "octahedron.h"

ENGINE_HEADER_BEGIN

Octahedron::Octahedron(Real radius, const Vec &position, const Mat &rotation)
    : Mesh(position, rotation), __radius(radius) {}

RayHitInfo Octahedron::hit_ray(const Ray &local_ray) const {
    RayHitInfo res = {0, 0};
    res |= hit_ray_on_face(local_ray, {1, 1, 1});
    res |= hit_ray_on_face(local_ray, {1, 1, -1});
    res |= hit_ray_on_face(local_ray, {1, -1, 1});
    res |= hit_ray_on_face(local_ray, {1, -1, -1});
    res |= hit_ray_on_face(local_ray, {-1, 1, 1});
    res |= hit_ray_on_face(local_ray, {-1, 1, -1});
    res |= hit_ray_on_face(local_ray, {-1, -1, 1});
    res |= hit_ray_on_face(local_ray, {-1, -1, -1});
    return res;
}

RayHitInfo Octahedron::hit_ray_on_face(const Ray &local_ray, const Vec &face_normal) const {
    Real k = dot(face_normal, local_ray.direction);
    if (k == 0)
        return {0, 0};

    Real time = (__radius - dot(face_normal, local_ray.origin)) / k;
    if (time < 0)
        return {0, 0};

    auto [x, y, z] = local_ray(time);
    if (x * (x - __radius * face_normal[X]) > 0 ||
        y * (y - __radius * face_normal[Y]) > 0 ||
        z * (z - __radius * face_normal[Z]) > 0)
        return {0, 0};

    return {1 / time, normalized(face_normal)};
}

ENGINE_HEADER_END
