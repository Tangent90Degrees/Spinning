#ifndef __DONUT_H__
#define __DONUT_H__

#include "mesh.h"

ENGINE_HEADER_BEGIN

class donut : public Mesh {
public:
    donut(Real major_radius, Real minor_radius,
          const Vec &position = 0, const Mat &rotation = 1);

    Real major_radius, minor_radius;

    RayHitInfo hit_ray(const Ray &local_ray) const override;
};

ENGINE_HEADER_END

#endif
