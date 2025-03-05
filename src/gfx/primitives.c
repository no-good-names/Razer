//
// Created by cp176 on 1/24/2025.
//

#include "primitives.h"
#include "typedef.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void DrawLine(const ivec2 start, const ivec2 end, const uint32_t color) {
	if (start[0] == end[0] && start[1] == end[1]) {
		setPixel(start[0], start[1], color);
		return;
	}

	int32_t x0 = (int32_t)round(start[0]), y0 = (int32_t)round(start[1]);
	const int32_t x1 = (int32_t)round(end[0]), y1 = (int32_t)round(end[1]);

	const int32_t dx = abs(x1 - x0), dy = abs(y1 - y0);
	// swap
	const int32_t sx = (x0 < x1) ? 1 : -1, sy = (y0 < y1) ? 1 : -1;
	int32_t err = dx - dy;

	while (1) {
		// if length is greater than the screen width or height then break
		if (x0 < -screen_size.x/2 || x0 >= screen_size.x || y0 < -screen_size.y/2 || y0 >= screen_size.y/2) {
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
void FillTriangle(ivec2 a, ivec2 b, ivec2 c, uint32_t color) {
	// Sort vertices by y-coordinate (a.y <= b.y <= c.y)
	if (a[1] > b[1]) swap(a, b);
	if (a[1] > c[1]) swap(a, c);
	if (b[1] > c[1]) swap(b, c);

	// Check for degenerate triangle (collapsed into a line or point)
	int total_height = c[1] - a[1];
	if (total_height == 0) {
		DrawLine(a, b, color);
		return;
	}

	// Draw the top half of the triangle (a to b)
	for (int y = a[1]; y <= b[1]; y++) {
		int segment_height = b[1] - a[1] + 1;
		if (segment_height == 0) continue; // Avoid division by zero

		float alpha = (float)(y - a[1]) / (float) total_height;
		float beta  = (float)(y - a[1]) / (float) segment_height;

		// Interpolate points along the edges
		iv2_t A = { a[0] + (int)((c[0] - a[0]) * alpha), y };
		iv2_t B = { a[0] + (int)((b[0] - a[0]) * beta), y };

		// Ensure A.x <= B.x
		if (A.x > B.x) swap(A, B);

		// Draw horizontal line
		for (int x = A.x; x <= B.x; x++) {
			setPixel(x, y, color);
		}
	}

	// Draw the bottom half of the triangle (b to c)
	for (int y = b[1]; y <= c[1]; y++) {
		int segment_height = c[1] - b[1] + 1;
		if (segment_height == 0) continue; // Avoid division by zero

		float alpha = (float)(y - a[1]) / total_height;
		float beta  = (float)(y - b[1]) / segment_height;

		// Interpolate points along the edges
		iv2_t A = { a[0] + (int)((c[0] - a[0]) * alpha), y };
		iv2_t B = { b[0] + (int)((c[0] - b[0]) * beta), y };

		// Ensure A.x <= B.x
		if (A.x > B.x) swap(A, B);

		// Draw horizontal line
		for (int x = A.x; x <= B.x; x++) {
			setPixel(x, y, color);
		}
	}
}
