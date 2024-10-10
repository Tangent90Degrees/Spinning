#ifndef __MAT_H__
#define __MAT_H__

#include "vec.h"

ENGINE_HEADER_BEGIN

/// @brief Describes a 3 by 3 matrix with floating-point entries. The sequence is stored as a 2-dimensional array of `Real`, representing entries in the 3-dimensional space.
struct Mat {

    static constexpr Size DIM = 3;

    constexpr Mat(Real xx, Real xy, Real xz,
                  Real yx, Real yy, Real yz,
                  Real zx, Real zy, Real zz)
        : __entries{xx, xy, xz,
                    yx, yy, yz,
                    zx, zy, zz} {}

    constexpr Mat(Real value)
        : Mat(value, 0, 0,
              0, value, 0,
              0, 0, value) {}

    /// @brief Accesses a row of entries of a specified axis.
    /// @param index Axis of row to access.
    /// @return A reference to an array of entries of the coordinates at axis `index`.
    constexpr auto &operator[](SpaceIndex index) {
        return __entries[index];
    }

    /// @brief Accesses a row of entries of a specified axis.
    /// @param index Axis of row to access.
    /// @return A reference to a real-only array of entries of the coordinates at axis `index`.
    constexpr auto &operator[](SpaceIndex index) const {
        return __entries[index];
    }

    /// @brief Accesses a row of entries of a specified axis.
    /// @param index Index of axis of row to access.
    /// @return A reference to an array of entries of the coordinates at axis `index`.
    constexpr auto &operator[](Index index) {
        _LIBCPP_ASSERT(index < DIM, "Invalid index");
        return __entries[index];
    }

    /// @brief Accesses a row of entries of a specified axis.
    /// @param index Index of axis of row to access.
    /// @return A reference to a read-only array of entries of the coordinates at axis `index`.
    constexpr auto &operator[](Index index) const {
        _LIBCPP_ASSERT(index < DIM, "Invalid index");
        return __entries[index];
    }

    constexpr Vec row(SpaceIndex index) const {
        return {__entries[index][X],
                __entries[index][Y],
                __entries[index][Z]};
    }

    constexpr Vec row(Index index) const {
        _LIBCPP_ASSERT(index < DIM, "Invalid index");
        return {__entries[index][X],
                __entries[index][Y],
                __entries[index][Z]};
    }

    constexpr Vec col(SpaceIndex index) const {
        return {__entries[X][index],
                __entries[Y][index],
                __entries[Z][index]};
    }

    constexpr Vec col(Index index) const {
        _LIBCPP_ASSERT(index < DIM, "Invalid index");
        return {__entries[X][index],
                __entries[Y][index],
                __entries[Z][index]};
    }

private:
    /// @brief Components of the matrix.
    Real __entries[DIM][DIM];
};

/// @brief Culculates the matrix representing rotation of an angle along an axis.
/// @param axis 
/// @param angle 
/// @return 
constexpr Mat rotation(SpaceIndex axis, Real angle) {
    Mat result = 1;
    Size next_axis = (axis + 1) % 3;
    Size last_axis = (axis + 2) % 3;
    Real cos_angle = cos(angle);
    Real sin_angle = sin(angle);
    result[next_axis][next_axis] = cos_angle;
    result[next_axis][last_axis] = -sin_angle;
    result[last_axis][next_axis] = sin_angle;
    result[last_axis][last_axis] = cos_angle;
    return result;
}

constexpr Vec operator*(const Mat &left, const Vec &right) {
    return left.col(X) * right[X] +
           left.col(Y) * right[Y] +
           left.col(Z) * right[Z];
}

constexpr Mat operator*(const Mat &left, const Mat &right) {
    return {dot(left.row(X), right.col(X)), dot(left.row(X), right.col(Y)), dot(left.row(X), right.col(Z)),
            dot(left.row(Y), right.col(X)), dot(left.row(Y), right.col(Y)), dot(left.row(Y), right.col(Z)),
            dot(left.row(Z), right.col(X)), dot(left.row(Z), right.col(Y)), dot(left.row(Z), right.col(Z))};
}

constexpr Mat transpose(const Mat &m) {
    return {m[X][X], m[Y][X], m[Z][X],
            m[X][Y], m[Y][Y], m[Z][Y],
            m[X][Z], m[Y][Z], m[Z][Z]};
}

ENGINE_HEADER_END

#endif // __MAT_H__