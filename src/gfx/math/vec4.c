#include "maths.h"
#include <math.h>

// add two vectors
v4_t v4_add(const v4_t a, const v4_t b) {
	return (v4_t) {
		.x = a.x + b.x,
		.y = a.y + b.y,
		.z = a.z + b.z,
        .z = a.w + b.w
	};
}

v4_t v4_sub(const v4_t a, const v4_t b) {
	return (v4_t) {
		.x = a.x - b.x,
		.y = a.y - b.y,
		.z = a.z - b.z,
        .w = a.w - b.w
	};
}

v4_t v4_mul(const v4_t a, const v4_t b) {
	return (v4_t) {
		.x = a.x * b.x,
		.y = a.y * b.y,
		.z = a.z * b.z,
        .w = a.w * b.w
	};
}

v4_t v4_normalize(const v4_t a) {
	float length = sqrtf(a.x * a.x + a.y * a.y + a.z * a.z + a.w * a.w);
	return (v4_t) {
		.x = a.x / length,
		.y = a.y / length,
		.z = a.z / length,
        .w = a.w / length
	};
}

float v4_dot(const v4_t a, const v4_t b) {
	return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

v4_t v4_negate(v4_t v) {
	return (v4_t) {
		.x = v.x * -1,
		.y = v.y * -1,
		.z = v.z * -1,
        .w = v.w * -1
	};
}

v4_t v4_scale(v4_t v, float s) {
	return (v4_t) {
		.x = v.x * s,
		.y = v.y * s,
		.z = v.z * s,
        .w = v.z * s
	};
}
