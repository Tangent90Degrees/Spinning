#ifndef __DONUT_H__
#define __DONUT_H__

#include "mesh.h"

ENGINE_HEADER_BEGIN

class donut : public mesh {
public:
    donut(real major_radius, real minor_radius,
          const vec &position = 0, const mat &rotation = 1);

    real major_radius, minor_radius;

    ray_hit_info hit_ray(const ray &local_ray) const override;
};

ENGINE_HEADER_END

#endif
