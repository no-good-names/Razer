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

void drawLine(const ivec2 start, const ivec2 end, uint32_t color);

INLINE void WireFrameTriangle(const ivec2 a, const ivec2 b, const ivec2 c, const uint32_t color) {
	drawLine(a, b, color);
	drawLine(b, c, color);
	drawLine(c, a, color);
}

WARNING("Incomplete") void FillTriangle(ivec2 a, ivec2 b, ivec2 c, uint32_t color);

#endif //PRIMITIVES_H
