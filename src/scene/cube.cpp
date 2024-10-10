#include "cube.h"

ENGINE_HEADER_BEGIN

Cube::Cube(Real edge_length, const Vec &position, const Mat &rotation)
    : Mesh(position, rotation), __half_edge_length(edge_length * 0.5) {}

RayHitInfo Cube::hit_ray(const Ray &local_ray) const {
    RayHitInfo hit(0, 0);
    hit |= hit_ray_on_face(local_ray, X, 1);
    hit |= hit_ray_on_face(local_ray, Y, 1);
    hit |= hit_ray_on_face(local_ray, Z, 1);
    hit |= hit_ray_on_face(local_ray, X, -1);
    hit |= hit_ray_on_face(local_ray, Y, -1);
    hit |= hit_ray_on_face(local_ray, Z, -1);
    return hit;
}

RayHitInfo Cube::hit_ray_on_face(const Ray &local_ray, SpaceIndex face_axis, Real face_direction) const {
    if (local_ray.direction[face_axis] == 0)
        return {0, 0};

    Real time = (face_direction * __half_edge_length - local_ray.origin[face_axis]) / local_ray.direction[face_axis];
    if (time < 0)
        return {0, 0};

    Vec point = local_ray(time);
    if (point[(face_axis + 1) % 3] > __half_edge_length ||
        point[(face_axis + 1) % 3] < -__half_edge_length ||
        point[(face_axis + 2) % 3] > __half_edge_length ||
        point[(face_axis + 2) % 3] < -__half_edge_length)
        return {0, 0};

    return {1 / time, Vec(face_axis, face_direction)};
}

ENGINE_HEADER_END
