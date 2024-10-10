#include "camera.h"

ENGINE_HEADER_BEGIN

Camera::Camera(Size width, Size height, Real lens, const Vec &position, const Mat &rotation)
    : SceneObject(position, rotation), width(width), height(height), lens(lens) {
}

ViewportPoint Camera::local_to_viewport(const Vec &local_point) const {
    Real depth = 1 / local_point[Z];
    int row = round(height * 0.5 - lens * depth * local_point[Y]);
    int col = round(width * 0.5 + lens * depth * local_point[X] * 2);
    return {BufferIndex(row, col), depth};
}

ViewportPoint Camera::world_to_viewport(const Vec &world_point) const {
    return local_to_viewport(world_to_local(world_point));
}

Ray Camera::viewport_to_local_ray(const BufferIndex &viewport_point, Real row_offset, Real col_offset) const {
    Real x = (viewport_point.col + col_offset - width * 0.5) * 0.5;
    Real y = -viewport_point.row - row_offset + height * 0.5;
    return {0, Vec(x, y, lens)};
}

Ray Camera::viewport_to_world_ray(const BufferIndex &viewport_point, Real row_offset, Real col_offset) const {
    return local_to_world(viewport_to_local_ray(viewport_point, row_offset, col_offset));
}

ENGINE_HEADER_END
