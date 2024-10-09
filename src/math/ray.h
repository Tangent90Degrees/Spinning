#ifndef __RAY_H__
#define __RAY_H__

#include "vec.h"

ENGINE_HEADER_BEGIN

struct ray_hit_info {

    constexpr ray_hit_info(real depth, const vec &normal)
        : depth(depth), normal(normal) {}

    real depth;
    vec normal;

    constexpr ray_hit_info &operator|=(const ray_hit_info &right) {
        if (right.depth > depth) {
            depth = right.depth;
            normal = right.normal;
        }
        return *this;
    }
};

struct ray {

    constexpr ray(const vec &origin, const vec &direction)
        : origin(origin), direction(direction) {}

    vec origin;
    vec direction;

    constexpr vec operator()(real time) const {
        return origin + direction * time;
    }
};

ENGINE_HEADER_END

#endif // __RAY_H__
