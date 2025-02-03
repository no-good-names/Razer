#include "maths.h"
#include <math.h>

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

v3_t v3_negate(v3_t v) {
	return (v3_t) {
		.x = v.x * -1,
		.y = v.y * -1,
		.z = v.z * -1
	};
}

v3_t v3_scale(v3_t v, float s) {
	return (v3_t) {
		.x = v.x * s,
		.y = v.y * s,
		.z = v.z * s
	};
}
