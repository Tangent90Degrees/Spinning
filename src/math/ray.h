#ifndef __RAY_H__
#define __RAY_H__

#include "vec.h"

ENGINE_HEADER_BEGIN

struct RayHitInfo {

    constexpr RayHitInfo(Real depth, const Vec &normal)
        : depth(depth), normal(normal) {}

    Real depth;
    Vec normal;

    constexpr RayHitInfo &operator|=(const RayHitInfo &right) {
        if (right.depth > depth) {
            depth = right.depth;
            normal = right.normal;
        }
        return *this;
    }
};

struct Ray {

    constexpr Ray(const Vec &origin, const Vec &direction)
        : origin(origin), direction(direction) {}

    Vec origin;
    Vec direction;

    constexpr Vec operator()(Real time) const {
        return origin + direction * time;
    }
};

ENGINE_HEADER_END

#endif // __RAY_H__
