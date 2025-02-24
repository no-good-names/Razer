//
// Created by cp176 on 1/24/2025.
//

#include "maths.h"

#include <math.h>

#include "mat3.h"

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

// TODO: 4x4 matrix rotation
// x ROTATION MAT REF:
// x,		y,		z
// 1,		0,		0
// 0,		cosA,	-sinA
// 0,		sinA,	cosA

// y ROTATION:
// x,		y,		z
// cosA,	0,		sinA
//	0,		1,		0
// -sinA,	0,		cosA

// z ROT:
//	x,		y,		z
//	cosA,	-sinA,	0
//	sinA,	cosA,	0
//	0,		0,		1

void rotate(const vec3 v, const vec3 rotation, vec3 out) {
	const float cosX = cosf(DEG2RAD(rotation[0]));
	const float sinX = sinf(DEG2RAD(rotation[0]));
	const float cosY = cosf(DEG2RAD(rotation[1]));
	const float sinY = sinf(DEG2RAD(rotation[1]));
	const float cosZ = cosf(DEG2RAD(rotation[2]));
	const float sinZ = sinf(DEG2RAD(rotation[2]));
	vec3 tmp0 = { 0 }, tmp1 = { 0 };
	// X:
	tmp0[0] = v[0];
	tmp0[1] = cosX * v[1] - sinX * v[2];
	tmp0[2] = sinX * v[1] + cosX * v[2];
	tmp1[0] = cosY * tmp0[0] + sinY * tmp0[2];
	tmp1[1] = tmp0[1];
	tmp1[2] = -sinY * tmp0[0] + cosY * tmp0[2];
	out[0] = cosZ * tmp1[0] - sinZ * tmp1[1];
	out[1] = sinZ * tmp1[0] + cosZ * tmp1[1];
	out[2] = tmp1[2];
}

