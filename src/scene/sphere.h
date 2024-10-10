#ifndef __SPHERE_H__
#define __SPHERE_H__

#include "mesh.h"

ENGINE_HEADER_BEGIN

class sphere : public Mesh {
public:
    sphere(Real radius, const Vec &position = 0, const Mat &rotation = 1);

    RayHitInfo hit_ray(const Ray &local_ray) const override;

private:
    Real radius;
};

ENGINE_HEADER_END

#endif // __SPHERE_H__