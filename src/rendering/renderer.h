#ifndef __RENDER_H__
#define __RENDER_H__

#include "buffer.h"
#include <iostream>
#include <unistd.h>

ENGINE_HEADER_BEGIN

class Render {
public:
    static constexpr Size MAX_WIDTH = 208;
    static constexpr Size MAX_HEIGHT = 65;

    Buffer<Real, MAX_HEIGHT, MAX_WIDTH> depth_buffer;
    Buffer<char, MAX_HEIGHT, MAX_WIDTH> pixel_buffer;

    Size width;
    Size height;

    Render(Size width, Size height, char background_pixel = ' ')
        : depth_buffer{0}, width(width), height(height) {
        pixel_buffer.fill(background_pixel);
        printf("\x1b[2J");
    }

    void clear(char background_pixel = ' ') {
        depth_buffer.fill(0);
        pixel_buffer.fill(background_pixel);
    }

    void put(BufferIndex index, Real depth, char pixel) {
        if (pixel_buffer.in_range(index) && depth > depth_buffer[index]) {
            depth_buffer[index] = depth;
            pixel_buffer[index] = pixel;
        }
    }

    void draw_buffer() const {
        // printf("\x1b[H");
        system("clear");
        for (auto row : Range(height)) {
            for (auto col : Range(width + 1)) {
                putchar(col ? pixel_buffer[row][col] : 10);
            }
        }
    }
};

ENGINE_HEADER_END

#endif
