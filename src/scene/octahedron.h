#ifndef __OCTAHEDRON_H__
#define __OCTAHEDRON_H__

#include "mesh.h"

ENGINE_HEADER_BEGIN

class Octahedron : public Mesh {
public:
    Octahedron(Real radius, const Vec &position = 0, const Mat &rotation = 1);

    RayHitInfo hit_ray(const Ray &local_ray) const override;

private:
    Real __radius;

    RayHitInfo hit_ray_on_face(const Ray &local_ray, const Vec &face_normal) const;
};

ENGINE_HEADER_END

#endif
