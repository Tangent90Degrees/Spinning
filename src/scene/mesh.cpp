#include "mesh.h"

ENGINE_HEADER_BEGIN

ray_hit_info mesh::hit_ray_on_face(const ray &local_ray, const vec &face_normal, real face_shift) {
    real k = dot(face_normal, local_ray.direction);
    if (k == 0)
        return {0, 0};

    real time = (face_shift - dot(face_normal, local_ray.origin)) / k;
    if (time < 0)
        return {0, 0};
        
    return {1 / time, normalized(face_normal)};
}

ENGINE_HEADER_END
