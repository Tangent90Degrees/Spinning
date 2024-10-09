#include "camera.h"

ENGINE_HEADER_BEGIN

camera::camera(int width, int height, real lens, const vec &position, const mat &rotation)
    : scene_object(position, rotation), width(width), height(height), lens(lens) {
}

viewport_point camera::local_to_viewport(const vec &local_point) const {
    real depth = 1 / local_point[Z];
    int row = round(height * 0.5 - lens * depth * local_point[Y]);
    int col = round(width * 0.5 + lens * depth * local_point[X] * 2);
    return {buffer_index(row, col), depth};
}

viewport_point camera::world_to_viewport(const vec &world_point) const {
    return local_to_viewport(world_to_local(world_point));
}

ray camera::viewport_to_local_ray(const buffer_index &viewport_point, real row_offset, real col_offset) const {
    real x = (-width * 0.5 + viewport_point.col + col_offset) * 0.5;
    real y = height * 0.5 - viewport_point.row - row_offset;
    return {0, vec(x, y, lens)};
}

ray camera::viewport_to_world_ray(const buffer_index &viewport_point, real row_offset, real col_offset) const {
    auto [_, direction] = viewport_to_local_ray(viewport_point, row_offset, col_offset);
    return {position, rotation * direction};
}

ENGINE_HEADER_END
