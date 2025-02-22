//
// Created by cp176 on 1/24/2025.
//

#include "maths.h"

#include <math.h>
void rotateX(const vec3 v, const float angle, vec3 out) {
	const float cosAngle = cosf(DEG2RAD(angle));
	const float sinAngle = sinf(DEG2RAD(angle));
	out[0] = v[0];
	out[1] = v[1] * cosAngle - v[2] * sinAngle;
	out[2] = v[1] * sinAngle + v[2] * cosAngle;
}

void rotateY(const vec3 v, const float angle, vec3 out) {
	const float cosAngle = cosf(DEG2RAD(angle));
	const float sinAngle = sinf(DEG2RAD(angle));
	out[0] = v[0] * cosAngle + v[2] * sinAngle;
	out[1] = v[1];
	out[2] = -v[0] * sinAngle + v[2] * cosAngle;
}

void rotateZ(const vec3 v, const float angle, vec3 out) {
	const float cosAngle = cosf(DEG2RAD(angle));
	const float sinAngle = sinf(DEG2RAD(angle));
	out[0] = v[0] * cosAngle - v[1] * sinAngle;
	out[1] = v[0] * sinAngle + v[1] * cosAngle;
	out[2] = v[2];
}

void rotate(const vec3 v, const vec3 rotation, vec3 out) {
    vec3 temp = {0}, temp2 = {0};
    rotateX(v, rotation[0], temp);
    rotateY(temp, rotation[1], temp2);
    rotateZ(temp2, rotation[2], out);
}
