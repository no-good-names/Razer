//
// Created by carp on 6/18/25.
//

#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include <stdint.h>
#include <cglm/cglm.h>

void set_pixel(const int32_t x, const int32_t y, const uint32_t color);
void get_pixel(const int32_t x, const int32_t y, uint32_t *color);
void draw_line(int ax, int ay, int bx, int by, uint32_t color);
void barycentric(ivec2 *pts, ivec2 P, vec3 out);
void triangle(ivec2 *pts, uint32_t color);
void render_wireframe(vec3 *v, ivec3 *f, int face_count, uint32_t color);
void render_triangle(vec3 *v, ivec3 *f, int face_count, uint32_t color);

#endif //PRIMITIVES_H
