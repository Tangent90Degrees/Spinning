#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "scene_object.h"
#include "../rendering/buffer.h"

ENGINE_HEADER_BEGIN

struct ViewportPoint {
    constexpr ViewportPoint(const BufferCoord &index, Real depth)
        : index(index), depth(depth) {}

    BufferCoord index;
    Real depth;
};

class Camera : public SceneObject {
public:
    Camera(Size width, Size height, Real lens,
           const Vec &position = 0,
           const Mat &rotation = 1);

    Size width, height;
    Real lens;

    ViewportPoint local_to_viewport(const Vec &local_point) const;
    ViewportPoint world_to_viewport(const Vec &world_point) const;

    Ray viewport_to_local_ray(const BufferCoord &viewport_point, Real row_offset = 0, Real col_offset = 0) const;
    Ray viewport_to_world_ray(const BufferCoord &viewport_point, Real row_offset = 0, Real col_offset = 0) const;
};

ENGINE_HEADER_END

#endif