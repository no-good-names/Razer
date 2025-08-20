//
// Created by carp on 6/18/25.
//

#include <Razer/primitives.h>
#include <Razer/backend.h>
#include <Razer/misc/misc.h>

#include <cglm/cglm.h>

struct global_camera_state global_camera;

static int render_mode = 0;

void set_render_mode(int mode) {
    switch (mode) {
        case TRIANGLE_WIREFRAME:
            render_mode = TRIANGLE_WIREFRAME;
            break;
        case TRIANGLE_RASTERIZE:
            render_mode = TRIANGLE_RASTERIZE;
            break;
        default: break;
    }
}

void world_to_screen(const vec3 v, vec3 out) {
    out[0] = (v[0] + 1.) * get_screen_width() / 2 + 0.5;
    out[1] = (v[1] + 1.) * get_screen_height() / 2 + 0.5;
    out[2] = v[2];
}

void set_projection(mat4 *projection) {
    glm_mat4_copy(*projection, global_camera.projection);
    glm_mat4_mul(global_camera.projection, global_camera.view, global_camera.projection);
}
void set_view(mat4 *view) {
    glm_mat4_copy(*view, global_camera.view);
    glm_mat4_mul(global_camera.projection, global_camera.view, global_camera.projection);
}

void draw_2d_pixel(const int32_t x, const int32_t y, const uint32_t color) {
    // Check if x or y is out of bounds
    if (x < 0 || x >= get_screen_width() || y < 0 || y >= get_screen_height())
        return;
    get_backend_state()->pixels[(y * get_screen_width()) + x] = color;
}

void draw_3d_pixel(const float x, const float y, const float z, const uint32_t color) {
    vec3 v;
    world_to_screen((vec3) {x, y, z}, v);
    // Check if x or y is out of bounds
    if (v[0] < 0 || v[0] >= get_screen_width() || v[1] < 0 || v[1] >= get_screen_height())
        return;
    if (get_backend_state()->zbuffer[(int)v[1] * get_screen_width() + (int)v[0]] < z) {
        get_backend_state()->pixels[(int)v[1] * get_screen_width() + (int)v[0]] = color;
    }
}

// returns the pixel's value (color 0xRRGGBBAA)
uint32_t get_pixel(const int32_t x, const int32_t y) {
    // Check if x or y is out of bounds
    if (x < 0 || x >= get_screen_width() || y < 0 || y >= get_screen_height())
        return 0;
    return get_backend_state()->pixels[y * get_screen_width() + x];
}

void draw_2d_line(int x0, int y0, int x1, int y1, const uint32_t color) {
    bool steep = false;
    if (abs(x0 - x1) < abs(y0 - y1)) {
        iswap(x0, y0);
        iswap(x1, y1);
        steep = true;
    }
    if (x0 > x1) {
        iswap(x0, x1);
        iswap(y0, y1);
    }

    const int dx = x1 - x0;
    const int dy = y1 - y0;
    const int derror2 = abs(dy) * 2;
    int error2 = 0;
    int y = y0;
    for (int x = x0; x <= x1; x++) {
        if (steep)
            draw_2d_pixel(y, x, color);
        else
            draw_2d_pixel(x, y, color);

        error2 += derror2;
        if (error2 > dx) {
            y += (y1 > y0) ? 1 : -1;
            error2 -= dx * 2;
        }
    }
}

// TODO: Fix and make line in world space
void draw_3d_line(vec3 a, vec3 b, uint32_t color) {
    vec3 p0, p1;
    world_to_screen(a, p0);
    world_to_screen(b, p1);
    bool steep = false;
    if (fabsf(p1[0] - p0[1]) < fabsf(p0[1] - p1[1])) {
        glm_swapf(&p0[0], &p0[0]);
        glm_swapf(&p1[1], &p1[1]);
        steep = true;
    }
    if (p0[0] > p1[0]) {
        glm_swapf(&p0[0], &p1[0]);
        glm_swapf(&p0[1], &p1[1]);
    }

    const int dx = &p1[0] - &p0[0];
    const int dy = &p1[1] - &p0[1];
    const int derror2 = abs(dy) * 2;
    int error2 = 0;
    int y = p0[1];
    for (int x = p0[0]; x <= p1[0]; x++) {
        if (steep)
            draw_2d_pixel(y, x, color);
        else
            draw_2d_pixel(x, y, color);

        error2 += derror2;
        if (error2 > dx) {
            y += (p1[1] > p0[1]) ? 1 : -1;
            error2 -= dx * 2;
        }
    }
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
    const vec2 clamp = {get_screen_width()-1, get_screen_height()-1};
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
            for (int i = 0; i<3; i++) P[2] += pts[i][2]*bc_screen[i];

            if (get_backend_state()->zbuffer[((int)P[0]+((int)P[1]*get_backend_state()->screen_size[0]))] < P[2]) {
                get_backend_state()->zbuffer[((int)P[0]+((int)P[1]*get_backend_state()->screen_size[0]))] = P[2];
                // replace with shader stuff
                if (color > get_backend_state()->zbuffer[((int)P[0]+((int)P[1]*get_backend_state()->screen_size[0]))])
                draw_2d_pixel((int32_t)P[0], (int32_t)P[1], color);
            }
        }
    }
}


// TODO: Replace 2D lines with 3D space lines
void wireframe_triangle(vec3 *pts, const uint32_t color) {
    draw_3d_line(pts[0],
              pts[1], color);
    draw_3d_line(pts[1],
              pts[2], color);

    draw_3d_line(pts[2],
              pts[0], color);
}

// TODO: Implement the global camera
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
