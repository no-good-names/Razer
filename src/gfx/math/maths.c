//
// Created by cp176 on 1/24/2025.
//

#include "maths.h"

#include <math.h>

void rotateX(vec3 v, float angle, vec3 out) {
	float cosAngle = cosf(angle);
	float sinAngle = sinf(angle);
	out[0] = v[0];
	out[1] = v[1] * cosAngle - v[2] * sinAngle;
	out[2] = v[1] * sinAngle + v[2] * cosAngle;
}

void rotateY(vec3 v, float angle, vec3 out) {
	float cosAngle = cosf(angle);
	float sinAngle = sinf(angle);
	out[0] = v[0] * cosAngle - v[2] * sinAngle;
	out[1] = v[1];
	out[2] = v[0] * sinAngle + v[2] * cosAngle;
}

void rotateZ(vec3 v, float angle, vec3 out) {
	float cosAngle = cosf(angle);
	float sinAngle = sinf(angle);
	out[0] = v[0] * cosAngle - v[1] * sinAngle;
	out[1] = v[0] * sinAngle + v[1] * cosAngle;
	out[2] = v[2];
}

void rotate_m(vec3 v, vec3 rotation, vec3 out) {
	rotateX(v, rotation[0], out);
	rotateY(v, rotation[1], out);
	rotateZ(v, rotation[2], out);
}

