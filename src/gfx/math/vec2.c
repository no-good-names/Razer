#include "maths.h"
#include <math.h>

// add two vectors
v2_t v2_add(const v2_t a, const v2_t b) {
	return (v2_t) {
		.x = a.x + b.x,
		.y = a.y + b.y
	};
}

v2_t v2_sub(const v2_t a, const v2_t b) {
	return (v2_t) {
		.x = a.x - b.x,
		.y = a.y - b.y
	};
}

v2_t v2_mul(const v2_t a, const v2_t b) {
	return (v2_t) {
		.x = a.x * b.x,
		.y = a.y * b.y
	};
}

v2_t v2_normalize(const v2_t a) {
	float length = sqrtf(a.x * a.x + a.y * a.y);
	return (v2_t) {
		.x = a.x / length,
		.y = a.y / length
	};
}

float v2_dot(const v2_t a, const v2_t b) {
	return (a.x * b.x) + (a.y * b.y);
}

float v2_length(v2_t a) {
	return sqrtf((a.x * a.x) + (a.y * a.y));
}

v2_t v2_negate(v2_t v) {
	return (v2_t) {
		.x = v.x * -1,
		.y = v.y * -1
	};
}

v2_t v2_scale(v2_t v, float s) {
	return (v2_t) {
		.x = v.x * s,
		.y = v.y * s
	};
}
