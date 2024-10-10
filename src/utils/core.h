#ifndef __CORE_H__
#define __CORE_H__

#include <iterator>
#include <math.h>

#define ENGINE_HEADER_BEGIN namespace Engine {

#define ENGINE_HEADER_END }

ENGINE_HEADER_BEGIN

using Bool = bool;

using Size = unsigned int;

using Index = unsigned int;

using Int = int;

/// @brief The type of floating-point values in engine.
typedef float Real;

constexpr Real sqr(Real x) { return x * x; }

constexpr Real sqrt_newton_raphson(Real x, Real curr, Real prev) {
    return curr == prev ? curr : sqrt_newton_raphson(x, 0.5 * (curr + x / curr), curr);
}

constexpr Real sqrt(Real x) {
    if (x < 0)
        return std::numeric_limits<Real>::quiet_NaN();
    if (x == std::numeric_limits<Real>::infinity())
        return std::numeric_limits<Real>::infinity();
    return sqrt_newton_raphson(x, x, 0);
}

ENGINE_HEADER_END

#endif // __CORE_H__