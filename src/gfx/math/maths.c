//
// Created by cp176 on 1/24/2025.
//

#include "maths.h"

#include <math.h>
#include <stdlib.h>

v3_t rotateX(v3_t v, float angle) {
	float cosAngle = cosf(angle);
	float sinAngle = sinf(angle);
	return (v3_t) {
		.x = v.x * cosAngle - v.z * sinAngle,
		.y = v.y,
		.z = v.x * sinAngle + v.z * cosAngle
	};
}

v3_t rotateY(v3_t v, float angle) {
	float cosAngle = cosf(angle);
	float sinAngle = sinf(angle);
	return (v3_t) {
		.x = v.x,
		.y = v.y * cosAngle - v.z * sinAngle,
		.z = v.y * sinAngle + v.z * cosAngle
	};
}

v3_t rotateZ(v3_t v, float angle) {
	float cosAngle = cosf(angle);
	float sinAngle = sinf(angle);
	return (v3_t) {
		.x = v.x * cosAngle - v.y * sinAngle,
		.y = v.x * sinAngle + v.y * cosAngle,
		.z = v.z
	};
}

void rotateX_m(vec3 v, float angle, vec3 out) {
	float cosAngle = cosf(angle);
	float sinAngle = sinf(angle);
	out[0] = v[0];
	out[1] = v[1] * cosAngle - v[2] * sinAngle;
	out[2] = v[1] * sinAngle + v[2] * cosAngle;
}

void rotateY_m(vec3 v, float angle, vec3 out) {
	float cosAngle = cosf(angle);
	float sinAngle = sinf(angle);
	out[0] = v[0] * cosAngle - v[2] * sinAngle;
	out[1] = v[1];
	out[2] = v[0] * sinAngle + v[2] * cosAngle;
}

void rotateZ_m(vec3 v, float angle, vec3 out) {
	float cosAngle = cosf(angle);
	float sinAngle = sinf(angle);
	out[0] = v[0] * cosAngle - v[1] * sinAngle;
	out[1] = v[0] * sinAngle + v[1] * cosAngle;
	out[2] = v[2];
}

void rotate_m(vec3 v, vec3 rotation, vec3 out) {
	rotateX_m(v, rotation[0], out);
	rotateY_m(v, rotation[1], out);
	rotateZ_m(v, rotation[2], out);
}

