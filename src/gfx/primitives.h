//
// Created by carp on 6/18/25.
//

#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include <stdint.h>

void set_pixel(const int32_t x, const int32_t y, const uint32_t color);
void get_pixel(const int32_t x, const int32_t y, uint32_t *color);
void draw_line(int ax, int ay, int bx, int by, uint32_t color);

#endif //PRIMITIVES_H
