//
// Created by cp176 on 1/24/2025.
//

#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include <stdint.h>
#include "math/maths.h"
#include "typedef.h"
#include "window.h"

void ProjectToCanvas(const vec3 v, ivec2 dest);

enum TriangleDrawType {
	TRIANGLE_FILLED,
	TRIANGLE_WIREFRAME
};

void SetDrawType(uint8_t type);

INLINE void NormalizeToPixel(float x, float y, int32_t *outX, int32_t *outY) {
	*outX = (int32_t)roundf((x) * 0.5f * (screen_size[0] - 1));
	*outY = (int32_t)roundf((y) * 0.5f * (screen_size[1] - 1)); // Flip Y-axis
}

INLINE void SetPixel(int32_t x, int32_t y, const uint32_t color) {
	// start at the middle of the screen
	x += screen_size[0]/2;
	y = (screen_size[1] / 2) - y - 1; // y flip
	// Check if x or y is out of bounds of the screen if so return
	if (x < 0 || x >= screen_size[0] || y < 0 || y >= screen_size[1]) {
		return;
	}
	pixels[(y * screen_size[0]) + x] = color;
}

void DrawLine(const ivec2 start, const ivec2 end, uint32_t color);

INLINE void WireFrameTriangle(const ivec2 a, const ivec2 b, const ivec2 c, const uint32_t color) {
	DrawLine(a, b, color);
	DrawLine(b, c, color);
	DrawLine(c, a, color);
}

void FillTriangle(ivec2 a, ivec2 b, ivec2 c, uint32_t color);

void RenderTriangle(ivec2 points[3], uint32_t color);

#endif //PRIMITIVES_H
