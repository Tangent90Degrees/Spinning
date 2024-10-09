#ifndef __BUFFER_H__
#define __BUFFER_H__

#include "../utils/core.h"
#include <string>

ENGINE_HEADER_BEGIN

struct buffer_index {
    constexpr buffer_index(int row, int col)
        : row(row), col(col) {}

    int row, col;
};

template <typename T, size_t ROWS, size_t COLS>
struct buffer {
    using data_type = T;
    using row_type = data_type (&)[COLS];
    using const_row_type = const data_type (&)[COLS];

    constexpr row_type operator[](size_t row) { return __data[row]; }
    constexpr const_row_type operator[](size_t row) const { return __data[row]; }

    constexpr data_type &operator[](buffer_index index) { return __data[index.row][index.col]; }
    constexpr data_type operator[](buffer_index index) const { return __data[index.row][index.col]; }

    void fill(data_type bit) {
        memset(__data, bit, ROWS * COLS * sizeof(data_type));
    }

    constexpr bool in_range(buffer_index index) const {
        return index.row >= 0 && index.col >= 0 && index.row < ROWS && index.col < COLS;
    }

    data_type __data[ROWS][COLS];
};

ENGINE_HEADER_END

#endif // __BUFFER_H__