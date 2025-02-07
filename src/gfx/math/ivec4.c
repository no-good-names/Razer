#include "maths.h"
#include <math.h>

// add two vectors
iv4_t iv4_add(const iv4_t a, const iv4_t b) {
	return (iv4_t) {
		.x = a.x + b.x,
		.y = a.y + b.y,
		.z = a.z + b.z,
        .w = a.w + b.w
	};
}

iv4_t iv4_sub(const iv4_t a, const iv4_t b) {
	return (iv4_t) {
		.x = a.x - b.x,
		.y = a.y - b.y,
		.z = a.z - b.z,
        .w = a.w - b.w
	};
}

iv4_t iv4_mul(const iv4_t a, const iv4_t b) {
	return (iv4_t) {
		.x = a.x * b.x,
		.y = a.y * b.y,
		.z = a.z * b.z,
        .w = a.w * b.w
	};
}

iv4_t iv4_normalize(const iv4_t a) {
	float length = sqrtf(a.x * a.x + a.y * a.y + a.z * a.z + a.w * a.w);
	return (iv4_t) {
		.x = a.x / length,
		.y = a.y / length,
		.z = a.z / length,
        .w = a.w / length
	};
}

float iv4_dot(const iv4_t a, const iv4_t b) {
	return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

float iv4_length(const iv4_t a) {
    return sqrtf(a.x * a.x + a.y * a.y + a.z * a.z + a.w * a.w);
}

iv4_t iv4_negate(iv4_t v) {
	return (iv4_t) {
		.x = v.x * -1,
		.y = v.y * -1,
		.z = v.z * -1,
        .w = v.w * -1
	};
}

iv4_t iv4_scale(iv4_t v, int s) {
	return (iv4_t) {
		.x = v.x * s,
		.y = v.y * s,
		.z = v.z * s,
        .w = v.z * s
	};
}
