#include "maths.h"
#include <math.h>

// add two vectors
iv3_t iv3_add(const iv3_t a, const iv3_t b) {
	return (iv3_t) {
		.x = a.x + b.x,
		.y = a.y + b.y,
		.z = a.z + b.z
	};
}

iv3_t iv3_sub(const iv3_t a, const iv3_t b) {
	return (iv3_t) {
		.x = a.x - b.x,
		.y = a.y - b.y,
		.z = a.z - b.z
	};
}

iv3_t iv3_mul(const iv3_t a, const iv3_t b) {
	return (iv3_t) {
		.x = a.x * b.x,
		.y = a.y * b.y,
		.z = a.z * b.z
	};
}

iv3_t iv3_normalize(const iv3_t a) {
	float length = sqrtf(a.x * a.x + a.y * a.y + a.z * a.z);
	return (iv3_t) {
		.x = a.x / length,
		.y = a.y / length,
		.z = a.z / length
	};
}

iv3_t iv3_cross(const iv3_t a, const iv3_t b) {
	return (iv3_t) {
		.x = a.y * b.z - a.z * b.y,
		.y = a.z * b.x - a.x * b.z,
		.z = a.x * b.y - a.y * b.x
	};
}

float iv3_dot(const iv3_t a, const iv3_t b) {
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

float iv3_length(iv3_t a) {
	return sqrtf(a.x * a.x + a.y * a.y + a.z * a.z);
}

iv3_t iv3_negate(iv3_t v) {
	return (iv3_t) {
		.x = v.x * -1,
		.y = v.y * -1,
		.z = v.z * -1
	};
}

iv3_t iv3_scale(iv3_t v, int s) {
	return (iv3_t) {
		.x = v.x * s,
		.y = v.y * s,
		.z = v.z * s
	};
}

