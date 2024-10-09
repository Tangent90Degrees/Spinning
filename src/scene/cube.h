#ifndef __CUBE_H__
#define __CUBE_H__

#include "mesh.h"

ENGINE_HEADER_BEGIN

class cube : public mesh {
public:
    cube(real edge_length, const vec &position = 0, const mat &rotation = 1);

    ray_hit_info hit_ray(const ray &local_ray) const override;

private:
    real half_edge_length;

    ray_hit_info hit_ray_on_face(const ray &local_ray, space_index face_axis, real face_direction) const;
};

ENGINE_HEADER_END

#endif // __CUBE_H__