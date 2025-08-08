//
// Created by carp on 6/18/25.
//

#include <Razer/primitives.h>
#include <Razer/backend.h>
#include <Razer/misc/misc.h>

#include <cglm/cglm.h>

int render_mode = 0;

void set_pixel(const int32_t x, const int32_t y, const uint32_t color) {
    // Check if x or y is out of bounds
    if (x < 0 || x >= get_screen_width() || y < 0 || y >= get_screen_height())
        return;
    pixels[(y * get_screen_width()) + x] = color;
}

void get_pixel(const int32_t x, const int32_t y, uint32_t *color) {
    // Check if x or y is out of bounds
    if (x < 0 || y >= get_screen_width() || y < 0 || y >= get_screen_height()) {
        return;
    }
    *color = pixels[(y * get_screen_width()) + x];
}

void draw_line(int ax, int ay, int bx, int by, const uint32_t color) {
    bool steep = false;
    if (abs(ax - bx) < abs(ay - by)) {
        iswap(ax, ay);
        iswap(bx, by);
        steep = true;
    }
    if (ax > bx) {
        iswap(ax, bx);
        iswap(ay, by);
    }

    const int dx = bx - ax;
    const int dy = by - ay;
    const int derror2 = abs(dy) * 2;
    int error2 = 0;
    int y = ay;
    for (int x = ax; x <= bx; x++) {
        if (steep)
            set_pixel(y, x, color);
        else
            set_pixel(x, y, color);

        error2 += derror2;
        if (error2 > dx) {
            y += (by > ay) ? 1 : -1;
            error2 -= dx * 2;
        }
    }
}

void world_to_screen(const vec3 v, vec3 out) {
    out[0] = (v[0] + 1.) * screen_size[0] / 2 + 0.5;
    out[1] = (v[1] + 1.) * screen_size[1] / 2 + 0.5;
    out[2] = v[2];
}

void barycentric(vec3 A, vec3 B, vec3 C, vec3 P, vec3 out) {
    vec3 a = {
        C[0] - A[0],
        B[0] - A[0],
        A[0] - P[0]
    };
    vec3 b = {
        C[1] - A[1],
        B[1] - A[1],
        A[1] - P[1]
    };
    vec3 u;
    glm_vec3_cross(a, b, u);
    if (fabsf(u[2]) > 1e-2) {
        glm_vec3_copy((vec3){1.0f-(u[0]+u[1])/u[2], u[1]/u[2], u[0]/u[2]}, out);
        return;
    }
    glm_vec3_copy((vec3){-1, 1, 1}, out);
}

void rasterized_triangle(vec3 *pts, const uint32_t color) {
    vec2 bboxmin = {  FLT_MAX,  FLT_MAX };
    vec2 bboxmax = { -FLT_MAX, -FLT_MAX };
    vec2 clamp = {screen_size[0]-1, screen_size[1]-1};
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j<2; j++) {
            bboxmin[j] = glm_max(0.0f, glm_min(bboxmin[j], pts[i][j]));
            bboxmax[j] = glm_min(clamp[j], glm_max(bboxmax[j], pts[i][j]));
        }
    }
    vec3 P;
    for (P[0] = bboxmin[0]; P[0] <= bboxmax[0]; P[0]++) {
        for (P[1] = bboxmin[1]; P[1] <= bboxmax[1]; P[1]++) {
            vec3 bc_screen;
            barycentric(pts[0], pts[1], pts[2], P, bc_screen);
            if (bc_screen[0] < 0 || bc_screen[1] < 0 || bc_screen[2] < 0) continue;
            P[2] = 0;
            for (int i = 0; i<3; i++) {
                P[2] += pts[i][2]*bc_screen[i];
            }
            if (zbuffer[(int)(P[0]+P[1]*screen_size[0])] < P[2]) {
                zbuffer[(int)(P[0]+P[1]*screen_size[0])] = P[2];
                set_pixel(P[0], P[1], color);
            }
        }
    }
}

void wireframe_triangle(vec3 *pts, uint32_t color) {
    draw_line((int)pts[0][0], (int)pts[0][1],
              (int)pts[1][0], (int)pts[1][1], color);

    draw_line((int)pts[1][0], (int)pts[1][1],
              (int)pts[2][0], (int)pts[2][1], color);

    draw_line((int)pts[2][0], (int)pts[2][1],
              (int)pts[0][0], (int)pts[0][1], color);
}

void render_triangle(const vec3 *v, ivec3 *f, const int nFaces, const uint32_t *colors) {
    for (int i = 0; i<nFaces; i++) {
        ivec3 face;
        glm_ivec3_copy(f[i], face);
        vec3 pts[3];
        for (int j = 0; j<3; j++) {
            world_to_screen(v[face[j]], pts[j]);
        }
        // colors will be replaced with shaders later
        if (render_mode == TRIANGLE_WIREFRAME)
            wireframe_triangle(pts, colors[i]);
        else
            rasterized_triangle(pts, colors[i]);
    }
}
