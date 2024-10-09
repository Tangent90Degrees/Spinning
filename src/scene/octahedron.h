#ifndef __OCTAHEDRON_H__
#define __OCTAHEDRON_H__

#include "mesh.h"

ENGINE_HEADER_BEGIN

class octahedron : public mesh {
public:
    octahedron(real radius, const vec &position = 0, const mat &rotation = 1);

    ray_hit_info hit_ray(const ray &local_ray) const override;

private:
    real __radius;

    ray_hit_info hit_ray_on_face(const ray &local_ray, const vec &face_normal) const;
};

ENGINE_HEADER_END

#endif
