#ifndef __CORE_H__
#define __CORE_H__

#include <iterator>
#include <math.h>

#define ENGINE_HEADER_BEGIN namespace engine {

#define ENGINE_HEADER_END }

ENGINE_HEADER_BEGIN

/// @brief The type of floating-point values in engine.
typedef float real;

constexpr real sqr(real x) { return x * x; }

constexpr real sqrt_newton_raphson(real x, real curr, real prev) {
    return curr == prev ? curr : sqrt_newton_raphson(x, 0.5 * (curr + x / curr), curr);
}

constexpr real sqrt(real x) {
    if (x < 0)
        return std::numeric_limits<real>::quiet_NaN();
    if (x == std::numeric_limits<real>::infinity())
        return std::numeric_limits<real>::infinity();
    return sqrt_newton_raphson(x, x, 0);
}

ENGINE_HEADER_END

#endif // __CORE_H__