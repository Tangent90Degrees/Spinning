#ifndef __SCENE_OBJECT_H__
#define __SCENE_OBJECT_H__

#include "../math/mat.h"
#include "../math/ray.h"

ENGINE_HEADER_BEGIN

class scene_object {
public:
    scene_object(const scene_object &) = delete;
    virtual ~scene_object() = default;

    vec position;
    mat rotation;

    vec local_to_world(const vec &local_point) const;
    vec world_to_local(const vec &world_point) const;

    ray local_to_world(const ray &local_ray) const;
    ray world_to_local(const ray &world_ray) const;

protected:
    scene_object(const vec &position = 0,
                 const mat &rotation = 1);
};

ENGINE_HEADER_END

#endif