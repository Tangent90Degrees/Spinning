#ifndef __MAT_H__
#define __MAT_H__

#include "vec.h"

ENGINE_HEADER_BEGIN

/// @brief Describes a 3 by 3 matrix with floating-point entries. The sequence is stored as a 2-dimensional array of `real`, representing entries in the 3-dimensional space.
struct mat {

    constexpr mat(real xx, real xy, real xz,
                  real yx, real yy, real yz,
                  real zx, real zy, real zz)
        : __entries{xx, xy, xz,
                    yx, yy, yz,
                    zx, zy, zz} {}

    constexpr mat(real value)
        : mat(value, 0, 0,
              0, value, 0,
              0, 0, value) {}

    /// @brief Accesses a row of entries of a specified axis.
    /// @param index Axis of row to access.
    /// @return A reference to an array of entries of the coordinates at axis `index`.
    constexpr auto &operator[](space_index index) {
        return __entries[index];
    }

    /// @brief Accesses a row of entries of a specified axis.
    /// @param index Axis of row to access.
    /// @return A reference to a real-only array of entries of the coordinates at axis `index`.
    constexpr auto &operator[](space_index index) const {
        return __entries[index];
    }

    /// @brief Accesses a row of entries of a specified axis.
    /// @param index Index of axis of row to access.
    /// @return A reference to an array of entries of the coordinates at axis `index`.
    constexpr auto &operator[](size_t index) {
        _LIBCPP_ASSERT(index < 3, "Invalid index");
        return __entries[index];
    }

    /// @brief Accesses a row of entries of a specified axis.
    /// @param index Index of axis of row to access.
    /// @return A reference to a read-only array of entries of the coordinates at axis `index`.
    constexpr auto &operator[](size_t index) const {
        _LIBCPP_ASSERT(index < 3, "Invalid index");
        return __entries[index];
    }

    constexpr vec row(space_index index) const {
        return {__entries[index][X],
                __entries[index][Y],
                __entries[index][Z]};
    }

    constexpr vec row(size_t index) const {
        _LIBCPP_ASSERT(index < 3, "Invalid index");
        return {__entries[index][X],
                __entries[index][Y],
                __entries[index][Z]};
    }

    constexpr vec col(space_index index) const {
        return {__entries[X][index],
                __entries[Y][index],
                __entries[Z][index]};
    }

    constexpr vec col(size_t index) const {
        _LIBCPP_ASSERT(index < 3, "Invalid index");
        return {__entries[X][index],
                __entries[Y][index],
                __entries[Z][index]};
    }

private:
    /// @brief Components of the matrix.
    real __entries[3][3];
};

/// @brief Culculates the matrix representing rotation of an angle along an axis.
/// @param axis 
/// @param angle 
/// @return 
constexpr mat rotation(space_index axis, real angle) {
    mat result = 1;
    size_t next_axis = (axis + 1) % 3;
    size_t last_axis = (axis + 2) % 3;
    real cos_angle = cos(angle);
    real sin_angle = sin(angle);
    result[next_axis][next_axis] = cos_angle;
    result[next_axis][last_axis] = -sin_angle;
    result[last_axis][next_axis] = sin_angle;
    result[last_axis][last_axis] = cos_angle;
    return result;
}

constexpr vec operator*(const mat &left, const vec &right) {
    return left.col(X) * right[X] +
           left.col(Y) * right[Y] +
           left.col(Z) * right[Z];
}

constexpr mat operator*(const mat &left, const mat &right) {
    return {dot(left.row(X), right.col(X)), dot(left.row(X), right.col(Y)), dot(left.row(X), right.col(Z)),
            dot(left.row(Y), right.col(X)), dot(left.row(Y), right.col(Y)), dot(left.row(Y), right.col(Z)),
            dot(left.row(Z), right.col(X)), dot(left.row(Z), right.col(Y)), dot(left.row(Z), right.col(Z))};
}

constexpr mat transpose(const mat &m) {
    return {m[X][X], m[Y][X], m[Z][X],
            m[X][Y], m[Y][Y], m[Z][Y],
            m[X][Z], m[Y][Z], m[Z][Z]};
}

ENGINE_HEADER_END

#endif // __MAT_H__