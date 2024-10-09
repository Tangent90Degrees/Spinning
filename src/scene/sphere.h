#ifndef __SPHERE_H__
#define __SPHERE_H__

#include "mesh.h"

ENGINE_HEADER_BEGIN

class sphere : public mesh {
public:
    sphere(real radius, const vec &position = 0, const mat &rotation = 1);

    ray_hit_info hit_ray(const ray &local_ray) const override;

private:
    real radius;
};

ENGINE_HEADER_END

#endif // __SPHERE_H__