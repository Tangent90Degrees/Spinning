#include "scene_object.h"

ENGINE_HEADER_BEGIN

vec scene_object::local_to_world(const vec &local_point) const {
    return rotation * local_point + position;
}

vec scene_object::world_to_local(const vec &world_point) const {
    return transpose(rotation) * (world_point - position);
}

ray scene_object::local_to_world(const ray &local_ray) const {
    return {local_to_world(local_ray.origin), rotation * local_ray.direction};
}

ray scene_object::world_to_local(const ray &world_ray) const {
    mat inverse_rotation = transpose(rotation);
    return {inverse_rotation * (world_ray.origin - position),
            inverse_rotation * world_ray.direction};
}

scene_object::scene_object(const vec &position, const mat &rotation)
    : position(position), rotation(rotation) {
}

ENGINE_HEADER_END