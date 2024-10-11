#ifndef __BUFFER_H__
#define __BUFFER_H__

#include "../utils/core.h"
#include <string>

ENGINE_HEADER_BEGIN

struct BufferCoord {
    constexpr BufferCoord(Int row, Int col)
        : row(row), col(col) {}

    Int row, col;
};

template <typename Data, Size ROWS, Size COLS>
struct Buffer {

    using Iterator = Data (*)[COLS];
    using ConstIterator = const Data (*)[COLS];

    constexpr auto &operator[](Index row) { return __data[row]; }
    constexpr auto &operator[](Index row) const { return __data[row]; }

    constexpr Data &operator[](BufferCoord index) { return __data[index.row][index.col]; }
    constexpr Data operator[](BufferCoord index) const { return __data[index.row][index.col]; }

    constexpr Iterator begin() { return __data; }
    constexpr ConstIterator begin() const { return __data; }

    constexpr Iterator end() { return __data + ROWS; }
    constexpr ConstIterator end() const { return __data + ROWS; }

    void fill(Data bit) {
        memset(__data, bit, ROWS * COLS * sizeof(Data));
    }

    constexpr Bool in_range(BufferCoord index) const {
        return index.row >= 0 && index.col >= 0 && index.row < ROWS && index.col < COLS;
    }

    Data __data[ROWS][COLS];
};

ENGINE_HEADER_END

#endif // __BUFFER_H__