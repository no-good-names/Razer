//
// Created by carp on 6/18/25.
//

#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include <stdint.h>
#include <cglm/cglm.h>

#define TRIANGLE_WIREFRAME 0x00
#define TRIANGLE_RASTERIZE 0x01

extern int render_mode;

static void set_render_mode(int mode) {
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

void draw_pixel(int32_t x, int32_t y, uint32_t color);
uint32_t get_pixel(int32_t x, int32_t y);
void draw_2d_line(int x0, int y0, int x1, int y1, uint32_t color);
void world_to_screen(const vec3 v, vec3 out);
void barycentric(vec3 A, vec3 B, vec3 C, vec3 P, vec3 out);
void rasterized_triangle(vec3 *pts, uint32_t color);
void render_triangle(const vec3 *v, ivec3 *f, int nFaces, const uint32_t *colors);

#endif //PRIMITIVES_H
