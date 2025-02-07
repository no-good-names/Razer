//
// Created by cp176 on 1/24/2025.
//

#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include <stdint.h>
#include "math/maths.h"
#include "typedef.h"

extern uint32_t *pixels;

void initPixels(uint32_t *buffer);

INLINE void setPixel(int32_t x, int32_t y, const uint32_t color) {
	// start at the middle of the screen
	x += SCREEN_WIDTH/2;
	y += SCREEN_HEIGHT/2;
	// Check if x or y is out of bounds of the screen
	if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT) {
		return;
	}
	pixels[(y * SCREEN_WIDTH) + x] = color;
}

void drawLine(iv2_t start, iv2_t end, uint32_t color);

INLINE void WireFrameTriangle(const iv2_t a, const iv2_t b, const iv2_t c, uint32_t color) {
	drawLine(a, b, color);
	drawLine(b, c, color);
	drawLine(c, a, color);
}

WARNING("Rasterizing is currently very buggy") void FillTriangle(iv2_t a, iv2_t b, iv2_t c, uint32_t color);

#endif //PRIMITIVES_H
