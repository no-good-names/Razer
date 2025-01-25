//
// Created by cp176 on 1/24/2025.
//

#include "maths.h"

#include <math.h>
#include <stdlib.h>

// add two vectors
v3_t v3_add(const v3_t a, const v3_t b) {
	return (v3_t) {
		.x = a.x + b.x,
		.y = a.y + b.y,
		.z = a.z + b.z
	};
}

v3_t v3_sub(const v3_t a, const v3_t b) {
	return (v3_t) {
		.x = a.x - b.x,
		.y = a.y - b.y,
		.z = a.z - b.z
	};
}

v3_t v3_mul(const v3_t a, const v3_t b) {
	return (v3_t) {
		.x = a.x * b.x,
		.y = a.y * b.y,
		.z = a.z * b.z
	};
}

v3_t v3_normalize(const v3_t a) {
	float length = sqrtf(a.x * a.x + a.y * a.y + a.z * a.z);
	return (v3_t) {
		.x = a.x / length,
		.y = a.y / length,
		.z = a.z / length
	};
}

v3_t v3_cross(const v3_t a, const v3_t b) {
	return (v3_t) {
		.x = a.y * b.z - a.z * b.y,
		.y = a.z * b.x - a.x * b.z,
		.z = a.x * b.y - a.y * b.x
	};
}

float v3_dot(const v3_t a, const v3_t b) {
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

float v3_length(v3_t a) {
	return sqrtf(a.x * a.x + a.y * a.y + a.z * a.z);
}

// B * t + A * (1-t)
float lerp(float a, float b, float t) {
	return a + t * (b - a);
}

int *Interpolate(v2_t start, v2_t end) {
	int length = end.y - start.y + 1; // Number of points to interpolate (inclusive)
	int *values = malloc(length * sizeof(int)); // Allocate memory for the result

	if (length <= 0) {
		return NULL; // Invalid input case, return NULL
	}

	float step = (float)(end.x - start.x) / (end.x - start.x); // Step size for interpolation
	for (int i = 0; i < length; ++i) {
		values[i] = (int)(start.x + step * i + 0.5f); // Interpolate and round to the nearest integer
	}

	return values;
}

v2_t v2_lerp(v2_t a, v2_t b, float t) {
	return (v2_t) {
		.x = lerp(a.x, b.x, t),
		.y = lerp(a.y, b.y, t)
	};
}
