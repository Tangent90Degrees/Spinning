#ifndef __SCENE_OBJECT_H__
#define __SCENE_OBJECT_H__

#include "../math/mat.h"
#include "../math/ray.h"

ENGINE_HEADER_BEGIN

class SceneObject {
public:
    SceneObject(const SceneObject &) = delete;
    virtual ~SceneObject() = default;

    Vec position;
    Mat rotation;

    Vec local_to_world(const Vec &local_point) const;
    Vec world_to_local(const Vec &world_point) const;

    Ray local_to_world(const Ray &local_ray) const;
    Ray world_to_local(const Ray &world_ray) const;

protected:
    SceneObject(const Vec &position = 0,
                const Mat &rotation = 1);
};

ENGINE_HEADER_END

#endif