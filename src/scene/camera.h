#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "scene_object.h"
#include "../rendering/buffer.h"

ENGINE_HEADER_BEGIN

struct viewport_point {
    constexpr viewport_point(const buffer_index &index, real depth)
        : index(index), depth(depth) {}

    buffer_index index;
    real depth;
};

class camera : public scene_object {
public:
    camera(int width, int height, real lens,
           const vec &position = 0,
           const mat &rotation = 1);

    int width, height;
    real lens;

    viewport_point local_to_viewport(const vec &local_point) const;
    viewport_point world_to_viewport(const vec &world_point) const;

    ray viewport_to_local_ray(const buffer_index &viewport_point, real row_offset = 0, real col_offset = 0) const;
    ray viewport_to_world_ray(const buffer_index &viewport_point, real row_offset = 0, real col_offset = 0) const;
};

ENGINE_HEADER_END

#endif