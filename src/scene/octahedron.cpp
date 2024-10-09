#include "octahedron.h"

ENGINE_HEADER_BEGIN

octahedron::octahedron(real radius, const vec &position, const mat &rotation)
    : mesh(position, rotation), __radius(radius) {}

ray_hit_info octahedron::hit_ray(const ray &local_ray) const {
    ray_hit_info res = {0, 0};
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

ray_hit_info octahedron::hit_ray_on_face(const ray &local_ray, const vec &face_normal) const {
    real k = dot(face_normal, local_ray.direction);
    if (k == 0)
        return {0, 0};

    real time = (__radius - dot(face_normal, local_ray.origin)) / k;
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
