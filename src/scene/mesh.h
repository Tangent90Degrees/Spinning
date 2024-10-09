#ifndef __MESH_H__
#define __MESH_H__

#include "scene_object.h"

ENGINE_HEADER_BEGIN

class mesh : public scene_object {
public:
    mesh(const vec &position = 0, const mat &rotation = 1)
        : scene_object(position, rotation) {}

    virtual ray_hit_info hit_ray(const ray &local_ray) const = 0;

protected:
    static ray_hit_info hit_ray_on_face(const ray &local_ray, const vec &face_normal, real face_shift);
};

ENGINE_HEADER_END

#endif