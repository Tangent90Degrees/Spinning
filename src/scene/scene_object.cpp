#include "scene_object.h"

ENGINE_HEADER_BEGIN

Vec SceneObject::local_to_world(const Vec &local_point) const {
    return rotation * local_point + position;
}

Vec SceneObject::world_to_local(const Vec &world_point) const {
    return transpose(rotation) * (world_point - position);
}

Ray SceneObject::local_to_world(const Ray &local_ray) const {
    return {local_to_world(local_ray.origin), rotation * local_ray.direction};
}

Ray SceneObject::world_to_local(const Ray &world_ray) const {
    Mat inverse_rotation = transpose(rotation);
    return {inverse_rotation * (world_ray.origin - position),
            inverse_rotation * world_ray.direction};
}

SceneObject::SceneObject(const Vec &position, const Mat &rotation)
    : position(position), rotation(rotation) {
}

ENGINE_HEADER_END