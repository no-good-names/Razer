#include <stdio.h>
#include <stdlib.h>

#include <Razer/Razer.h>

int main(int argc, char *argv[]) {
    init_video(800, 600, 1);
    // ivec2 pts[3] = {
    //     {450, 150},
    //     {250, 450},
    //     {650, 450}
    // };

    vec3 v[3] = {
        {0.5f, -0.5f, 0.0f},
        {-0.5f, -0.5f, 0.0f},
        {0.0f, 0.5f, 0.0f}
    };

    ivec3 f[1] = {
        {0, 1, 2}
    };

    while (!quit) {
        update_events();

        // triangle(pts, 0xFF00FF00);
        render_triangle(v, f, 1, 0xFF00FF00);
        // render_wireframe(v, f, 1, 0xFFFF0000);

        update_video();
    }
    destroy_video();
    return 0;
}
