//
// Created by cp176 on 1/24/2025.
//

#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include <stdint.h>
#include <stdlib.h>
#include "math/maths.h"
#include "typedef.h"

extern uint32_t *pixels;
void initPixels(uint32_t *buffer);
void setPixel(int32_t x, int32_t y, const uint32_t color);

void drawLine(iv2_t start, iv2_t end, uint32_t color);
void WireFrameTriangle(iv2_t a, iv2_t b, iv2_t c, uint32_t color);
WARNING("Filled triangles slow down randomly, beware") void FilledTriangle(iv2_t a, iv2_t b, iv2_t c, uint32_t color);

#endif //PRIMITIVES_H
