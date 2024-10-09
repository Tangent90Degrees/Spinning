#include "cube.h"

ENGINE_HEADER_BEGIN

cube::cube(real edge_length, const vec &position, const mat &rotation)
    : mesh(position, rotation), half_edge_length(edge_length * 0.5) {}

ray_hit_info cube::hit_ray(const ray &local_ray) const {
    ray_hit_info hit(0, 0);
    hit |= hit_ray_on_face(local_ray, X, 1);
    hit |= hit_ray_on_face(local_ray, Y, 1);
    hit |= hit_ray_on_face(local_ray, Z, 1);
    hit |= hit_ray_on_face(local_ray, X, -1);
    hit |= hit_ray_on_face(local_ray, Y, -1);
    hit |= hit_ray_on_face(local_ray, Z, -1);
    return hit;
}

ray_hit_info cube::hit_ray_on_face(const ray &local_ray, space_index face_axis, real face_direction) const {
    if (local_ray.direction[face_axis] == 0)
        return {0, 0};

    real time = (face_direction * half_edge_length - local_ray.origin[face_axis]) / local_ray.direction[face_axis];
    if (time < 0)
        return {0, 0};

    vec point = local_ray(time);
    if (point[(face_axis + 1) % 3] > half_edge_length ||
        point[(face_axis + 1) % 3] < -half_edge_length ||
        point[(face_axis + 2) % 3] > half_edge_length ||
        point[(face_axis + 2) % 3] < -half_edge_length)
        return {0, 0};

    return {1 / time, vec(face_axis, face_direction)};
}

ENGINE_HEADER_END
