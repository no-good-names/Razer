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
void world_to_screen(const vec3 v, vec3 out);
void barycentric(vec3 A, vec3 B, vec3 C, vec3 P, vec3 out);
void triangle(vec3 *pts, const uint32_t color);
void render_triangle(vec3 *v, ivec3 *f, int nFaces, uint32_t *colors);

#endif //PRIMITIVES_H
