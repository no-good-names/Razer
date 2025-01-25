//
// Created by cp176 on 1/24/2025.
//

#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include <stdint.h>
#include "math/maths.h"

void drawLine(void (setPixel)(int32_t x, int32_t y, uint32_t color), v2_t start, v2_t end, uint32_t color);
void WireFrameTriangle(void (setPixel)(int32_t x, int32_t y, uint32_t color), v2_t a, v2_t b, v2_t c, uint32_t color);
void FilledTriangle(void (setPixel)(int32_t x, int32_t y, uint32_t color), v2_t a, v2_t b, v2_t c, uint32_t color);

#endif //PRIMITIVES_H
