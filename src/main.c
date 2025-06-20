#include <stdio.h>
#include <stdlib.h>
#include <SDL3/SDL.h>

#include <cglm/cglm.h>

#include "gfx/backend.h"
#include "gfx/primitives.h"

void project(const vec3 v, ivec2 out) {
    out[0] = (v[0] + 1.) * get_screen_width() / 2;
    out[1] = (v[1] + 1.) * get_screen_height() / 2;
}

void barycentric(ivec2 *pts, ivec2 P, vec3 out) {
    vec3 a = {
        (float)(pts[2][0] - pts[0][0]),
        (float)(pts[1][0] - pts[0][0]),
        (float)(pts[0][0] - P[0])
    };
    vec3 b = {
        (float)(pts[2][1] - pts[0][1]),
        (float)(pts[1][1] - pts[0][1]),
        (float)(pts[0][1] - P[1])
    };
    vec3 u;
    glm_vec3_cross(a, b, u);
    if (fabsf(u[2]) < 1) {
        glm_vec3_copy((vec3){-1, 1, 1}, out);
        return;
    }
    glm_vec3_copy((vec3){1.0f-(u[0]+u[1]/u[2]), u[1]/u[2], u[0]/u[2]}, out);
}

void triangle(ivec2 *pts, uint32_t color) {
    ivec2 bboxmin = {get_screen_width()-1, get_screen_height()-1};
    ivec2 bboxmax = {0, 0};
    ivec2 clamp = {get_screen_width()-1, get_screen_height()-1};
    for (int i = 0; i < 3; i++) {
        bboxmin[0] = glm_imax(0, glm_imin(bboxmin[0], pts[i][0]));
        bboxmin[1] = glm_imax(0, glm_imin(bboxmin[1], pts[i][1]));

        bboxmax[0] = glm_imin(clamp[0], glm_imax(bboxmax[0], pts[i][0]));
        bboxmax[1] = glm_imin(clamp[1], glm_imax(bboxmax[1], pts[i][1]));
    }
    ivec2 P;
    for (P[0] = bboxmin[0]; P[0] <= bboxmax[0]; P[0]++) {
        for (P[1] = bboxmin[1]; P[1] <= bboxmax[1]; P[1]++) {
            vec3 bc_screen;
            barycentric(pts, P, bc_screen);
            if (bc_screen[0] < 0 || bc_screen[1] < 0 || bc_screen[2] < 0) continue;
            set_pixel(P[0], P[1], color);
        }
    }
}

void render_wireframe(vec3 *v, ivec3 *f, int face_count, uint32_t color) {
    for (int i = 0; i < face_count; i++) {
        ivec3 face;
        glm_ivec3_copy(f[i], face);
        for (int j = 0; j < 3; j++) {
            vec3 v0;
            glm_vec3_copy(v0, v[face[j]]);
            vec3 v1;
            glm_vec3_copy(v1, v[face[(j + 1) % 3]]);

            int x0 = (int)((v0[0] + 1.0f) * get_screen_width()  / 2.0f);
            int y0 = (int)((v0[1] + 1.0f) * get_screen_height() / 2.0f);
            int x1 = (int)((v1[0] + 1.0f) * get_screen_width()  / 2.0f);
            int y1 = (int)((v1[1] + 1.0f) * get_screen_height() / 2.0f);

            draw_line(x0, y0, x1, y1, color);
        }
    }
}

// TODO: Fix whatever is wrong with this
void render_triangle(vec3 *v, ivec3 *f, int face_count, uint32_t color) {
    for (int i = 0; i < face_count; i++) {
        ivec3 face;
        glm_ivec3_copy(f[i], face);
        ivec2 sc[3];
        for (int j = 0; j < 3; j++) {
            vec3 wc;
            glm_vec3_copy(v[face[j]], wc);
            sc[j][0] = (int)((wc[0] + 1.0f) * get_screen_width()  / 2.0f);
            sc[j][1] = (int)((wc[1] + 1.0f) * get_screen_height() / 2.0f);
        }
        triangle(sc, color);
    }
}


int main(int argc, char *argv[]) {
    init_video(900, 600, 1);
    ivec2 pts[3] = {
        {450, 150},
        {650, 450},
        {250, 450}
    };

    while (!quit) {
        update_events();

        triangle(pts, 0xFF00FF00);

        update_video();
    }
    destroy_video();
    return 0;
}
