#ifndef __VEC_H__
#define __VEC_H__

#include "../utils/range.h"
#include <tuple>
#include <utility>

ENGINE_HEADER_BEGIN

/// @brief Describes the key used to access coordinates in 3-dimensional space.
enum space_index {
    X = 0,
    Y = 1,
    Z = 2
};

/// @brief Describes an 3-dimensional vector with floating-point entries. The sequence is stored as an array of `Real`, representing coordinates in the 3-dimensional space.
struct vec {

    constexpr vec(real x, real y, real z)
        : __entries{x, y, z} {}

    constexpr vec(real value)
        : __entries{value, value, value} {}

    constexpr vec(space_index axis, real value)
        : __entries{0} {
        __entries[axis] = value;
    }

    /// @brief Accesses an coordinate of a specified axis.
    /// @param index Axis of coordinate to access.
    /// @return A reference to the entry of the coordinates at axis `index`.
    real &operator[](space_index index) {
        return __entries[index];
    }

    /// @brief Accesses an coordinate of a specified axis.
    /// @param index Axis of coordinate to access.
    /// @return The entry of the coordinates at axis `index`.
    constexpr real operator[](space_index index) const {
        return __entries[index];
    }

    /// @brief Accesses an coordinate of a specified axis.
    /// @param index Index of axis of coordinate to access.
    /// @return A reference to the entry of the coordinates at axis `index`.
    real &operator[](size_t index) {
        _LIBCPP_ASSERT(index < 3, "Index out of bounds");
        return __entries[index];
    }

    /// @brief Accesses an coordinate of a specified axis.
    /// @param index Index of axis of coordinate to access.
    /// @return A reference to the entry of the coordinates at axis `index`.
    constexpr real operator[](size_t index) const {
        _LIBCPP_ASSERT(index < 3, "Index out of bounds");
        return __entries[index];
    }

    vec &operator+=(const vec &right) {
        __entries[X] += right[X];
        __entries[Y] += right[Y];
        __entries[Z] += right[Z];
        return *this;
    }

    vec &operator-=(const vec &right) {
        __entries[X] -= right[X];
        __entries[Y] -= right[Y];
        __entries[Z] -= right[Z];
        return *this;
    }

    template <size_t INDEX>
    std::tuple_element_t<INDEX, vec> &get() {
        return __entries[INDEX];
    }

    template <size_t INDEX>
    std::tuple_element_t<INDEX, vec> get() const {
        return __entries[INDEX];
    }

private:
    /// @brief Components of the vector.
    real __entries[3];
};

/// @brief Vector comparison, equal.
/// @param left Left vector to compare.
/// @param right Right vector to compare.
/// @return `true` if left and right are equal, `false` otherwise.
constexpr bool operator==(const vec &left, const vec &right) {
    return left[X] == right[X] &&
           left[Y] == right[Y] &&
           left[Z] == right[Z];
}

/// @brief Array comparison, not equal.
/// @param left Left vector to compare.
/// @param right Right vector to compare.
/// @return `true` if left and right are not equal, `false` otherwise.
constexpr bool operator!=(const vec &left, const vec &right) {
    return left[X] != right[X] ||
           left[Y] != right[Y] ||
           left[Z] != right[Z];
}

/// @brief Positive sign.
/// @param right Right vector.
/// @return `right` vector.
constexpr vec operator+(const vec &right) {
    return right;
}

/// @brief Negative sign.
/// @param right Right vector.
/// @return The negation of `right` vector.
constexpr vec operator-(const vec &right) {
    return {-right[X],
            -right[Y],
            -right[Z]};
}

/// @brief Adds two vectors.
/// @param left The first of two vectors to be added by the `+` operation.
/// @param right The second of two vectors to be added by the `+` operation.
/// @return The vector that results from the addition of the two vectors whose value are specified by the parameter inputs.
constexpr vec operator+(const vec &left, const vec &right) {
    return {left[X] + right[X],
            left[Y] + right[Y],
            left[Z] + right[Z]};
}

constexpr vec operator-(const vec &left, const vec &right) {
    return {left[X] - right[X],
            left[Y] - right[Y],
            left[Z] - right[Z]};
}

constexpr vec operator*(real left, const vec &right) {
    return {left * right[X],
            left * right[Y],
            left * right[Z]};
}

constexpr vec operator*(const vec &left, real right) {
    return {left[X] * right,
            left[Y] * right,
            left[Z] * right};
}

constexpr vec operator/(const vec &left, real right) {
    return left * (1 / right);
}

constexpr real dot(const vec &left, const vec &right) {
    return left[X] * right[X] +
           left[Y] * right[Y] +
           left[Z] * right[Z];
}

constexpr real sqr_norm(const vec &v) {
    return dot(v, v);
}

constexpr real norm(const vec &v) {
    return sqrt(sqr_norm(v));
}

constexpr vec normalized(const vec &v) {
    real norm_v = norm(v);
    return norm_v ? v / norm(v) : v;
}

ENGINE_HEADER_END

namespace std {

    template <>
    struct tuple_size<engine::vec> : public integral_constant<size_t, 3> {};

    template <size_t INDEX>
    struct tuple_element<INDEX, engine::vec> : public tuple_element<INDEX, tuple<engine::real, engine::real, engine::real>> {};

} // namespace std

#endif