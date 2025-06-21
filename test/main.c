#include <stdio.h>
#include <stdlib.h>

#include <Razer/Razer.h>

uint32_t color(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    return ((uint32_t)a << 24) | ((uint32_t)g << 16) | ((uint32_t)r << 8) | (uint32_t)b;
}

int main(int argc, char *argv[]) {
    init_video(800, 600, 1);

    const vec3 v[9] = {
        {0.5f, -0.5f, 0.0f},
        {-0.5f, -0.5f, 0.0f},
        {0.0f, 0.5f, -2.0f},

        {0.7f, -0.7f, -1.0f},
        {-0.5f, -0.7f, 1.0f},
        {0.2f, 0.3f, 0.0f},

        {0.7f, -0.3f, 0.0f},
        {-0.7f, -0.7f, -2.0f},
        {-0.2f, 0.5f, 0.0f}
    };

    ivec3 f[3] = {
        {0, 1, 2},
        {3, 4, 5},
        {6, 7, 8}
    };

    uint32_t colors[3] = {
        color(255, 0, 0, 255),
        color(0, 255, 0, 255),
        color(0, 0, 255, 255)
    };

    while (!quit) {
        update_events();
        // clear screen (pixel and z-buffer) every frame
        clear_screen();

        for (int i = 0; i<3; i++) {
            ivec3 face;
            glm_ivec3_copy(f[i], face);
            vec3 pts[3];
            for (int j = 0; j<3; j++) {
                project(v[face[j]], pts[j]);
            }
            triangle(pts, colors[i]);
        }

        update_video();
    }
    destroy_video();
    free(zbuffer);
    return 0;
}
