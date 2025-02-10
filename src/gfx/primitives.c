//
// Created by cp176 on 1/24/2025.
//

#include "primitives.h"
#include "typedef.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void drawLine(iv2_t start, iv2_t end, uint32_t color) {
	if (start.x == end.x && start.y == end.y) {
		setPixel(start.x, start.y, color);
		return;
	}

	int32_t x0 = (int32_t)round(start.x), y0 = (int32_t)round(start.y);
	const int32_t x1 = (int32_t)round(end.x), y1 = (int32_t)round(end.y);

	const int32_t dx = abs(x1 - x0), dy = abs(y1 - y0);
	// swap
	const int32_t sx = (x0 < x1) ? 1 : -1, sy = (y0 < y1) ? 1 : -1;
	int32_t err = dx - dy;

	while (1) {
		// if length is greater than the screen width or height then break
		if (x0 < -screen_size.x/2 || x0 >= screen_size.y/2 || y0 < -screen_size.x/2 || y0 >= screen_size.y/2) {
			break;
		}
		setPixel(x0, y0, color);
		if (x0 == x1 && y0 == y1) break;

		const int e2 = 2 * err;
		if (e2 > -dy) {
			err -= dy;
			x0 += sx;
		}
		if (e2 < dx) {
			err += dx;
			y0 += sy;
		}
	}
}

// https://github.com/ssloy/tinyrenderer/wiki/Lesson-2:-Triangle-rasterization-and-back-face-culling
void FillTriangle(iv2_t a, iv2_t b, iv2_t c, uint32_t color) {
	// Sort vertices by y-coordinate (a.y <= b.y <= c.y)
	if (a.y > b.y) swap(a, b);
	if (a.y > c.y) swap(a, c);
	if (b.y > c.y) swap(b, c);

	// Check for degenerate triangle (collapsed into a line or point)
	int total_height = c.y - a.y;
	if (total_height == 0) {
		drawLine(a, b, color);
		return;
	}

	// Draw the top half of the triangle (a to b)
	for (int y = a.y; y <= b.y; y++) {
		int segment_height = b.y - a.y + 1;
		if (segment_height == 0) continue; // Avoid division by zero

		float alpha = (float)(y - a.y) / (float) total_height;
		float beta  = (float)(y - a.y) / (float) segment_height;

		// Interpolate points along the edges
		iv2_t A = { a.x + (int)((c.x - a.x) * alpha), y };
		iv2_t B = { a.x + (int)((b.x - a.x) * beta), y };

		// Ensure A.x <= B.x
		if (A.x > B.x) swap(A, B);

		// Draw horizontal line
		for (int x = A.x; x <= B.x; x++) {
			setPixel(x, y, color);
		}
	}

	// Draw the bottom half of the triangle (b to c)
	for (int y = b.y; y <= c.y; y++) {
		int segment_height = c.y - b.y + 1;
		if (segment_height == 0) continue; // Avoid division by zero

		float alpha = (float)(y - a.y) / total_height;
		float beta  = (float)(y - b.y) / segment_height;

		// Interpolate points along the edges
		iv2_t A = { a.x + (int)((c.x - a.x) * alpha), y };
		iv2_t B = { b.x + (int)((c.x - b.x) * beta), y };

		// Ensure A.x <= B.x
		if (A.x > B.x) swap(A, B);

		// Draw horizontal line
		for (int x = A.x; x <= B.x; x++) {
			setPixel(x, y, color);
		}
	}
}
