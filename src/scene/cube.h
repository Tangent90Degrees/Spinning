#ifndef __CUBE_H__
#define __CUBE_H__

#include "mesh.h"

ENGINE_HEADER_BEGIN

class Cube : public Mesh {
public:
    Cube(Real edge_length, const Vec &position = 0, const Mat &rotation = 1);

    RayHitInfo hit_ray(const Ray &local_ray) const override;

private:
    Real __half_edge_length;

    RayHitInfo hit_ray_on_face(const Ray &local_ray, SpaceIndex face_axis, Real face_direction) const;
};

ENGINE_HEADER_END

#endif // __CUBE_H__