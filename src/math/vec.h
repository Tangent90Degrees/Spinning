#ifndef __VEC_H__
#define __VEC_H__

#include "../utils/range.h"
#include <tuple>
#include <utility>

ENGINE_HEADER_BEGIN

/// @brief Describes the key used to access coordinates in 3-dimensional space.
enum SpaceIndex {
    X = 0,
    Y = 1,
    Z = 2
};

/// @brief Describes an 3-dimensional vector with floating-point entries. The sequence is stored as an array of `Real`, representing coordinates in the 3-dimensional space.
struct Vec {

    static constexpr Size DIM = 3;

    constexpr Vec(Real x, Real y, Real z)
        : __entries{x, y, z} {}

    constexpr Vec(Real value)
        : __entries{value, value, value} {}

    constexpr Vec(SpaceIndex axis, Real value)
        : __entries{0} {
        __entries[axis] = value;
    }

    /// @brief Accesses an coordinate of a specified axis.
    /// @param index Axis of coordinate to access.
    /// @return A reference to the entry of the coordinates at axis `index`.
    Real &operator[](SpaceIndex index) {
        return __entries[index];
    }

    /// @brief Accesses an coordinate of a specified axis.
    /// @param index Axis of coordinate to access.
    /// @return The entry of the coordinates at axis `index`.
    constexpr Real operator[](SpaceIndex index) const {
        return __entries[index];
    }

    /// @brief Accesses an coordinate of a specified axis.
    /// @param index Index of axis of coordinate to access.
    /// @return A reference to the entry of the coordinates at axis `index`.
    constexpr Real &operator[](Index index) {
        _LIBCPP_ASSERT(index < DIM, "Index out of bounds");
        return __entries[index];
    }

    /// @brief Accesses an coordinate of a specified axis.
    /// @param index Index of axis of coordinate to access.
    /// @return A reference to the entry of the coordinates at axis `index`.
    constexpr Real operator[](Index index) const {
        _LIBCPP_ASSERT(index < DIM, "Index out of bounds");
        return __entries[index];
    }

    Vec &operator+=(const Vec &right) {
        __entries[X] += right[X];
        __entries[Y] += right[Y];
        __entries[Z] += right[Z];
        return *this;
    }

    Vec &operator-=(const Vec &right) {
        __entries[X] -= right[X];
        __entries[Y] -= right[Y];
        __entries[Z] -= right[Z];
        return *this;
    }

    template <size_t INDEX>
    std::tuple_element_t<INDEX, Vec> &get() {
        return __entries[INDEX];
    }

    template <size_t INDEX>
    std::tuple_element_t<INDEX, Vec> get() const {
        return __entries[INDEX];
    }

private:
    /// @brief Components of the vector.
    Real __entries[DIM];
};

/// @brief Vector comparison, equal.
/// @param left Left vector to compare.
/// @param right Right vector to compare.
/// @return `true` if left and right are equal, `false` otherwise.
constexpr bool operator==(const Vec &left, const Vec &right) {
    return left[X] == right[X] &&
           left[Y] == right[Y] &&
           left[Z] == right[Z];
}

/// @brief Array comparison, not equal.
/// @param left Left vector to compare.
/// @param right Right vector to compare.
/// @return `true` if left and right are not equal, `false` otherwise.
constexpr Bool operator!=(const Vec &left, const Vec &right) {
    return left[X] != right[X] ||
           left[Y] != right[Y] ||
           left[Z] != right[Z];
}

/// @brief Positive sign.
/// @param right Right vector.
/// @return `right` vector.
constexpr Vec operator+(const Vec &right) {
    return right;
}

/// @brief Negative sign.
/// @param right Right vector.
/// @return The negation of `right` vector.
constexpr Vec operator-(const Vec &right) {
    return {-right[X],
            -right[Y],
            -right[Z]};
}

/// @brief Adds two vectors.
/// @param left The first of two vectors to be added by the `+` operation.
/// @param right The second of two vectors to be added by the `+` operation.
/// @return The vector that results from the addition of the two vectors whose value are specified by the parameter inputs.
constexpr Vec operator+(const Vec &left, const Vec &right) {
    return {left[X] + right[X],
            left[Y] + right[Y],
            left[Z] + right[Z]};
}

constexpr Vec operator-(const Vec &left, const Vec &right) {
    return {left[X] - right[X],
            left[Y] - right[Y],
            left[Z] - right[Z]};
}

constexpr Vec operator*(Real left, const Vec &right) {
    return {left * right[X],
            left * right[Y],
            left * right[Z]};
}

constexpr Vec operator*(const Vec &left, Real right) {
    return {left[X] * right,
            left[Y] * right,
            left[Z] * right};
}

constexpr Vec operator/(const Vec &left, Real right) {
    return left * (1 / right);
}

constexpr Real dot(const Vec &left, const Vec &right) {
    return left[X] * right[X] +
           left[Y] * right[Y] +
           left[Z] * right[Z];
}

constexpr Real sqr_norm(const Vec &v) {
    return dot(v, v);
}

constexpr Real norm(const Vec &v) {
    return sqrt(sqr_norm(v));
}

constexpr Vec normalized(const Vec &v) {
    Real norm_v = norm(v);
    return norm_v ? v / norm(v) : v;
}

ENGINE_HEADER_END

namespace std {

    template <>
    struct tuple_size<Engine::Vec> : public integral_constant<size_t, 3> {};

    template <size_t INDEX>
    struct tuple_element<INDEX, Engine::Vec> : public tuple_element<INDEX, tuple<Engine::Real, Engine::Real, Engine::Real>> {};

} // namespace std

#endif