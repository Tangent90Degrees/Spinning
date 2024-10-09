#ifndef __RANGE_H__
#define __RANGE_H__

#include "core.h"

ENGINE_HEADER_BEGIN

struct Range {

    struct Iterator {
        constexpr Iterator(int current, int step)
            : __current(current), __step(step) {}

        constexpr bool operator!=(const Iterator &other) const {
            return __current != other.__current;
        }

        constexpr int operator*() const {
            return __current;
        }

        constexpr Iterator &operator++() {
            __current += __step;
            return *this;
        }

    private:
        int __current, __step;
    };

    constexpr Range(int start, int end, int step = 1)
        : __start(start), __step(step), __num_of_steps((end - start) / step) {}

    constexpr Range(int end)
        : Range(0, end, 1) {}

    constexpr Iterator begin() const {
        return {__start, __step};
    }

    constexpr Iterator end() const {
        return {__start + __step * __num_of_steps, __step};
    }

private:
    int __start, __step, __num_of_steps;
};

ENGINE_HEADER_END

#endif // __RANGE_H__