#include <stdio.h>
#include <stdlib.h>

#include <Razer/Razer.h>

int main(int argc, char *argv[]) {
    init_video(800, 600, 1);

    vec3 v[4] = {
        {-0.5f, 0.5f, 0.0f}, // ftl 0
        {0.5f, 0.5f, 0.0f}, // ftr 1
        {-0.5f, -0.5f, 0.0f}, // fbl 2
        {0.5f, -0.5f, 0.0f}, // fbr 3
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
        glm_rotate_make(rotation, glm_rad(angle), (vec3){0, 1, 0});
        glm_translate_make(translation, (vec3){0.0f, 0.0f, 2.0f});
        glm_mat4_mul(scale, rotation, model);
        glm_mat4_mul(translation, model, model);
        glm_mat4_mul(projection, model, mout);

        // Apply rotation to vertices
        vec3 projected_v[4];
        for (int i = 0; i < 4; i++) {

            vec4 temp = {v[i][0], v[i][1], v[i][2], 1.0f};
            glm_mat4_mulv(mout, temp, temp); // transform
            projected_v[i][0] = temp[0] / temp[3]; // perspective divide
            projected_v[i][1] = temp[1] / temp[3];
            projected_v[i][2] = temp[2] / temp[3];
        }

        render_triangle(projected_v, f, 2, colors);

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
