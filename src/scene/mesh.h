#ifndef __MESH_H__
#define __MESH_H__

#include "scene_object.h"

ENGINE_HEADER_BEGIN

class Mesh : public SceneObject {
public:
    Mesh(const Vec &position = 0, const Mat &rotation = 1)
        : SceneObject(position, rotation) {}

    virtual RayHitInfo hit_ray(const Ray &local_ray) const = 0;
};

ENGINE_HEADER_END

#endif