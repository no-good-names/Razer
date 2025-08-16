#include <stdio.h>
#include <stdlib.h>

#include <Razer/Razer.h>

/*
 * THIS IS THE TEST FILE NOT THE LIBRARY
 */

int main(int argc, char *argv[]) {
    init_video(800, 600, 1);


    //      btl4              btr5
    //
    //   ftl0              ftr1
    //
    //
    //     bbl6              bbr7
    //
    //   fbl2              fbr3
    // ftl, ftr, fbl
    // ftr, fbl, fbr

    vec3 v[8] = {
        {-1.0f, 1.0f, -1.0f}, // ftl 0
        {1.0f, 1.0f, -1.0f}, // ftr 1
        {-1.0f, -1.0f, -1.0f}, // fbl 2
        {1.0f, -1.0f, -1.0f}, // fbr 3

        {-1.0f, 1.0f, 1.0f}, // btl 4
        {1.0f, 1.0f, 1.0f}, // btr 5
        {-1.0f, -1.0f, 1.0f}, // bbl 6
        {1.0f, -1.0f, 1.0f} // bbr 7
    };

    ivec3 f[12] = {
        {0, 1, 2},
        {1, 2, 3},
        {4, 6, 7},
        {4, 5, 7},
        {5, 7, 3},
        {5, 1, 3},
        {4, 0, 6},
        {0, 2, 6},
        {4, 5, 1},
        {4, 0, 1},
        {6, 7, 3},
        {6, 2, 3}
    };

    uint32_t colors[12] = {
        color(255, 0, 0, 255),
        color(255, 0, 0, 255),
        color(255, 255, 0, 255),
        color(255, 255, 0, 255),
        color(0xFF, 0xA5, 0, 255),
        color(0xFF, 0xA5, 0, 255),
        color(0, 255, 0, 255),
        color(0, 255, 0, 255),
        color(0, 0, 255, 255),
        color(0, 0, 255, 255),
        color(255, 0, 255, 255),
        color(255, 0, 255, 255),
    };

    set_render_mode(TRIANGLE_RASTERIZE);
    float angle = 0.0f;
    mat4 projection;
    glm_perspective(glm_rad(60.0f), 800.0f/600.0f, 0.1f, 100.0f, projection);

    while (!quit) {
        angle += 0.5f;
        update_events();
        // clear screen (pixel and z-buffer) every frame
        clear_screen();

        mat4 rotation, translation, scale, model, mout;
        glm_scale_make(scale, (vec3) {1, 1, 1});
        glm_rotate_make(rotation, glm_rad(angle), (vec3){0, 1, 1});
        glm_translate_make(translation, (vec3){0.0f, 0.0f, 10.0f});
        glm_mat4_mul(scale, rotation, model);
        glm_mat4_mul(translation, model, model);
        glm_mat4_mul(projection, model, mout);

        // Apply rotation to vertices
        vec3 projected_v[8];
        for (int i = 0; i < 8; i++) {

            vec4 temp = {v[i][0], v[i][1], v[i][2], 1.0f};
            glm_mat4_mulv(mout, temp, temp);
            projected_v[i][0] = temp[0] / temp[3];
            projected_v[i][1] = temp[1] / temp[3];
            projected_v[i][2] = temp[2] / temp[3];
        }

        render_triangle(projected_v, f, 12, colors);

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
        if (key[SDL_SCANCODE_W]) {
            glm_translate(projection, (vec3) {0, 0, -0.01f});
        }
        if (key[SDL_SCANCODE_A]) {
            glm_translate(projection, (vec3) {-0.01f, 0, 0});
        }
        if (key[SDL_SCANCODE_S]) {
            glm_translate(projection, (vec3) {0, 0, 0.01f});
        }
        if (key[SDL_SCANCODE_D]) {
            glm_translate(projection, (vec3) {0.01f, 0, 0});
        }


        update_video();
    }
    destroy_video();
    return 0;
}
