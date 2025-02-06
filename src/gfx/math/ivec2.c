#include "maths.h"
#include <math.h>

// add two vectors
iv2_t iv2_add(const iv2_t a, const iv2_t b) {
	return (iv2_t) {
		.x = a.x + b.x,
		.y = a.y + b.y
	};
}

iv2_t iv2_sub(const iv2_t a, const iv2_t b) {
	return (iv2_t) {
		.x = a.x - b.x,
		.y = a.y - b.y
	};
}

iv2_t iv2_mul(const iv2_t a, const iv2_t b) {
	return (iv2_t) {
		.x = a.x * b.x,
		.y = a.y * b.y
	};
}

iv2_t iv2_normalize(const iv2_t a) {
	float length = sqrtf(a.x * a.x + a.y * a.y);
	return (iv2_t) {
		.x = a.x / length,
		.y = a.y / length
	};
}

float iv2_dot(const iv2_t a, const iv2_t b) {
	return (a.x * b.x) + (a.y * b.y);
}

float iv2_length(iv2_t a) {
	return sqrtf((a.x * a.x) + (a.y * a.y));
}

iv2_t iv2_negate(iv2_t v) {
	return (iv2_t) {
		.x = v.x * -1,
		.y = v.y * -1
	};
}

iv2_t iv2_scale(iv2_t v, int s) {
	return (iv2_t) {
		.x = v.x * s,
		.y = v.y * s
	};
}
