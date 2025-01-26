//
// Created by cp176 on 1/24/2025.
//

#include "primitives.h"

#include <math.h>

void drawLine(void (setPixel)(int32_t x, int32_t y, uint32_t color), v2_t start, v2_t end, uint32_t color) {
	if (start.x == end.x && start.y == end.y) {
		setPixel(start.x, start.y, color);
		return;
	}

	int x0 = (int)start.x, y0 = (int)start.y;
	int x1 = (int)end.x, y1 = (int)end.y;

	int dx = abs(x1 - x0), dy = abs(y1 - y0);
	int sx = (x0 < x1) ? 1 : -1;
	int sy = (y0 < y1) ? 1 : -1;
	int err = dx - dy;

	while (1) {
		setPixel(x0, y0, color);
		if (x0 == x1 && y0 == y1) break;

		int e2 = 2 * err;
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

void WireFrameTriangle(void (setPixel)(int32_t x, int32_t y, uint32_t color), v2_t a, v2_t b, v2_t c, uint32_t color) {
	drawLine(setPixel, a, b, color);
	drawLine(setPixel, b, c, color);
	drawLine(setPixel, c, a, color);
}

void FilledTriangle(void (setPixel)(int32_t x, int32_t y, uint32_t color), v2_t a, v2_t b, v2_t c, uint32_t color) {
	// sort vertices by y
	if (a.y > b.y) swap(a, b);
	if (a.y > c.y) swap(a, c);
	if (b.y > c.y) swap(b, c);

	// calculate the slope of the two lines
	const float invslope1 = (b.x - a.x) / (b.y - a.y);
	const float invslope2 = (c.x - a.x) / (c.y - a.y);

	// calculate the x values for the edges
	float curx1 = a.x;
	float curx2 = a.x;

	// draw the triangle
	for (int scanlineY = a.y; scanlineY <= b.y; scanlineY++) {
		drawLine(setPixel, (v2_t) {curx1, scanlineY}, (v2_t) {curx2, scanlineY}, color);
		curx1 += invslope1;
		curx2 += invslope2;
	}

	// calculate the slope of the two lines
	const float invslope3 = (c.x - b.x) / (c.y - b.y);

	// calculate the x values for the edges
	curx1 = b.x;

	// draw the triangle
	for (int scanlineY = b.y; scanlineY <= c.y; scanlineY++) {
		drawLine(setPixel, (v2_t) {curx1, scanlineY}, (v2_t) {curx2, scanlineY}, color);
		curx1 += invslope3;
		curx2 += invslope2;
	}
}

