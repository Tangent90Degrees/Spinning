#ifndef __RENDER_H__
#define __RENDER_H__

#include "buffer.h"
#include <iostream>
#include <unistd.h>

ENGINE_HEADER_BEGIN

constexpr size_t MAX_WIDTH = 208;
constexpr size_t MAX_HEIGHT = 65;

class render {
public:
    buffer<real, MAX_HEIGHT, MAX_WIDTH> depth_buffer;
    buffer<char, MAX_HEIGHT, MAX_WIDTH> pixel_buffer;

    size_t width;
    size_t height;

    render(size_t width, size_t height, char background_pixel = ' ')
        : depth_buffer{0}, width(width), height(height) {
        pixel_buffer.fill(background_pixel);
        printf("\x1b[2J");
    }

    void clear(char background_pixel = ' ') {
        depth_buffer.fill(0);
        pixel_buffer.fill(background_pixel);
    }

    void put(buffer_index index, real depth, char pixel) {
        if (pixel_buffer.in_range(index) && depth > depth_buffer[index]) {
            depth_buffer[index] = depth;
            pixel_buffer[index] = pixel;
        }
    }

    void draw_buffer() const {
        // printf("\x1b[H");
        system("clear");
        for (size_t row = 0; row < height; ++row) {
            for (size_t col = 0; col <= width; ++col) {
                putchar(col ? pixel_buffer[row][col] : 10);
            }
        }
    }
};

ENGINE_HEADER_END

#endif
