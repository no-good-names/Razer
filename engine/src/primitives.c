//
// Created by carp on 6/18/25.
//

#include <Razer/primitives.h>
#include <Razer/backend.h>
#include <Razer/misc/misc.h>

#include <cglm/cglm.h>

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

void project(const vec3 v, ivec2 out) {
    out[0] = (v[0] + 1.) * screen_size[0] / 2;
    out[1] = (v[1] + 1.) * screen_size[1] / 2;
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
    glm_vec3_copy((vec3){1.0f-((u[0]+u[1])/u[2]), u[1]/u[2], u[0]/u[2]}, out);
}

void triangle(ivec2 *pts, const uint32_t color) {
    ivec2 bboxmin = {screen_size[0]-1, screen_size[1]-1};
    ivec2 bboxmax = {0, 0};
    ivec2 clamp = {screen_size[0]-1, screen_size[1]-1};
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

void render_wireframe(vec3 *v, ivec3 *f, const int face_count, const uint32_t color) {
    for (int i = 0; i < face_count; i++) {
        ivec3 face;
        glm_ivec3_copy(f[i], face);
        for (int j = 0; j < 3; j++) {
            vec3 v0;
            glm_vec3_copy(v[face[j]], v0);
            vec3 v1;
            glm_vec3_copy(v[face[(j + 1) % 3]], v1);

            int x0 = (int)((v0[0] + 1.0f) * screen_size[0]  / 2.0f);
            int y0 = (int)((v0[1] + 1.0f) * screen_size[1] / 2.0f);
            int x1 = (int)((v1[0] + 1.0f) * screen_size[0]  / 2.0f);
            int y1 = (int)((v1[1] + 1.0f) * screen_size[1] / 2.0f);

            draw_line(x0, y0, x1, y1, color);
        }
    }
}

void render_triangle(vec3 *v, ivec3 *f, const int face_count, const uint32_t color) {
    for (int i = 0; i < face_count; i++) {
        ivec3 face;
        glm_ivec3_copy(f[i], face);
        ivec2 sc[3];
        for (int j = 0; j < 3; j++) {
            vec3 wc;
            glm_vec3_copy(v[face[j]], wc);
            sc[j][0] = (int)((wc[0] + 1.0f) * screen_size[0]  / 2.0f);
            sc[j][1] = (int)((wc[1] + 1.0f) * screen_size[1] / 2.0f);
        }
        triangle(sc, color);
    }
}
