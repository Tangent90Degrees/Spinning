#include "scene/camera.h"
#include "scene/cube.h"
#include "scene/sphere.h"
#include "scene/octahedron.h"
#include "scene/donut.h"
#include "rendering/renderer.h"
#include <sys/ioctl.h>

using namespace Engine;

BufferCoord get_window_size() {
    winsize window_size;
    ioctl(fileno(stdout), TIOCGWINSZ, &window_size);
    return BufferCoord(window_size.ws_row, window_size.ws_col);
}

int main() {
    Render render(160, 44);

    Real a, b, c;

    // sphere spinning_obj(15);
    Cube spinning_obj(30);
    // Octahedron spinning_obj(30);
    // donut spinning_obj(15, 5);
    Camera cam(160, 44, 40, {0, 0, -60});
    constexpr Vec light = normalized({-2, -1, 3});

    while (true) {
        render.clear();

        auto window_size = get_window_size();
        render.width = window_size.col;
        render.height = window_size.row;
        cam.width = window_size.col;
        cam.height = window_size.row;

        spinning_obj.rotation = rotation(X, a) * rotation(Y, b) * rotation(Z, c);

        for (int row = 0; row < cam.height; ++row) {
            for (int col = 0; col < cam.width; ++col) {
                auto ray = spinning_obj.world_to_local(cam.viewport_to_world_ray({row, col}));
                auto hit = spinning_obj.hit_ray(ray);
                hit.normal = spinning_obj.rotation * hit.normal;

                render.depth_buffer[row][col] = hit.depth;
                if (hit.depth) {
                    int shade = round(-dot(hit.normal, light) * 11);
                    shade = shade < 0 ? 0 : shade;
                    render.pixel_buffer[row][col] = ".,-~:;!=*#@$"[shade];
                }
            }
        }

        render.draw_buffer();

        a += 0.005;
        b += 0.003;
        c += 0.002;
        usleep(3000);
    }
}