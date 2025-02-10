//
// Created by cp176 on 1/24/2025.
//

#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include <stdint.h>
#include "math/maths.h"
#include "typedef.h"
#include "window.h"

INLINE void setPixel(int32_t x, int32_t y, const uint32_t color) {
	// start at the middle of the screen
	x += screen_size.x/2;
	y += screen_size.y/2;
	// Check if x or y is out of bounds of the screen
	if (x < 0 || x >= screen_size.x || y < 0 || y >= screen_size.y) {
		return;
	}
	pixels[(y * screen_size.x) + x] = color;
}

void drawLine(iv2_t start, iv2_t end, uint32_t color);

INLINE void WireFrameTriangle(const iv2_t a, const iv2_t b, const iv2_t c, uint32_t color) {
	drawLine(a, b, color);
	drawLine(b, c, color);
	drawLine(c, a, color);
}

WARNING("Incomplete") void FillTriangle(iv2_t a, iv2_t b, iv2_t c, uint32_t color);

#endif //PRIMITIVES_H
