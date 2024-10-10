#ifndef __RANGE_H__
#define __RANGE_H__

#include "core.h"

ENGINE_HEADER_BEGIN

struct Range {

    struct Iterator {
        constexpr Iterator(Int current, Int step)
            : __current(current), __step(step) {}

        constexpr Bool operator!=(const Iterator &other) const {
            return __current != other.__current;
        }

        constexpr Int operator*() const {
            return __current;
        }

        constexpr Iterator &operator++() {
            __current += __step;
            return *this;
        }

    private:
        Int __current, __step;
    };

    constexpr Range(Int start, Int end, Int step = 1)
        : __start(start), __step(step), __num_of_steps((end - start) / step) {}

    constexpr Range(Int end)
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