#include <stdio.h>
#include <stdlib.h>

#include <Razer/Razer.h>

int main(int argc, char *argv[]) {
    init_video(800, 600, 1);

    const vec3 v[4] = {
        {-0.5f, 0.5f, 0.0f},
        {0.5f, 0.5f, 0.0f},
        {-0.5f, -0.5f, 0.0f},
        {0.5f, -0.5f, 0.0f}
    };

    ivec3 f[2] = {
        {0, 1, 2},
        {1, 2, 3}
    };

    uint32_t colors[2] = {
        color(255, 0, 0, 255),
        color(255, 0, 0, 255)
    };

    set_render_mode(TRIANGLE_RASTERIZE);
    while (!quit) {
        update_events();
        // clear screen (pixel and z-buffer) every frame
        clear_screen();
        render_triangle(v, f, 2, colors);

        const uint8_t *key = SDL_GetKeyboardState(NULL);
        if (key[SDL_SCANCODE_ESCAPE]) {
            quit = 1;
        }
        if (key[SDL_SCANCODE_1]) {
            set_render_mode(TRIANGLE_RASTERIZE);
        }
        if (key[SDL_SCANCODE_2]) {
            set_render_mode(TRIANGLE_WIREFRAME);
        }

        update_video();
    }
    destroy_video();
    return 0;
}
