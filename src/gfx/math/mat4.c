//
// Created by cp176 on 2/23/2025.
//

#include "mat4.h"

#include "maths.h"

void mat4_scale(const mat4 m, const vec3 s, mat4 out) {
	out[0][0] = m[0][0] * s[0]; out[0][1] = m[0][1]; 		out[0][2] = m[0][2];		out[0][3] = m[0][3];
	out[1][0] = m[1][0]; 		out[1][1] = m[1][1] * s[1]; out[1][2] = m[1][2];		out[1][3] = m[1][3];
	out[2][0] = m[2][0]; 		out[2][1] = m[2][1]; 		out[2][2] = m[2][2] * s[2]; out[2][3] = m[2][3];
	out[3][0] = m[3][0]; 		out[3][1] = m[3][1]; 		out[3][2] = m[3][2];		out[3][3] = m[3][3];
}

void mat4_translate(const mat4 m, const vec3 t, mat4 out) {
	out[0][0] = m[0][0]; out[0][1] = m[0][1]; out[0][2] = m[0][2]; out[0][3] = m[0][3] + t[0];
	out[1][0] = m[1][0]; out[1][1] = m[1][1]; out[1][2] = m[1][2]; out[1][3] = m[1][3] + t[1];
	out[2][0] = m[2][0]; out[2][1] = m[2][1]; out[2][2] = m[2][2]; out[2][3] = m[2][3] + t[2];
	out[3][0] = m[3][0]; out[3][1] = m[3][1]; out[3][2] = m[3][2];
}

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

void mat4_rotate(const mat4 v, const vec3 rotation, mat4 out) {
	const float cosX = cosf(DEG2RAD(rotation[0]));
	const float sinX = sinf(DEG2RAD(rotation[0]));
	const float cosY = cosf(DEG2RAD(rotation[1]));
	const float sinY = sinf(DEG2RAD(rotation[1]));
	const float cosZ = cosf(DEG2RAD(rotation[2]));
	const float sinZ = sinf(DEG2RAD(rotation[2]));
	mat4 x = {
        {1, 0, 0, 0},
        {0, cosX, -sinX, 0},
        {0, sinX, cosX, 0},
        {0, 0, 0, 1}
    };
	mat4 y = {
        {cosY, 0, sinY, 0},
        {0, 1, 0, 0},
        {-sinY, 0, cosY, 0},
        {0, 0, 0, 1}
    };
	mat4 z = {
        {cosZ, -sinZ, 0, 0},
        {sinZ, cosZ, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
    };

	mat4_mul_mat4(x, y, x);
	mat4_mul_mat4(x, z, out);
}

void mat4_rotate_vec3(const vec3 v, const vec3 rotation, vec3 out) {

	const float cosX = cosf(DEG2RAD(rotation[0]));
	const float sinX = sinf(DEG2RAD(rotation[0]));
	const float cosY = cosf(DEG2RAD(rotation[1]));
	const float sinY = sinf(DEG2RAD(rotation[1]));
	const float cosZ = cosf(DEG2RAD(rotation[2]));
	const float sinZ = sinf(DEG2RAD(rotation[2]));
	mat4 x = {
		{1, 0, 0, 0},
		{0, cosX, -sinX, 0},
		{0, sinX, cosX, 0},
		{0, 0, 0, 1}
	};
	mat4 y = {
		{cosY, 0, sinY, 0},
		{0, 1, 0, 0},
		{-sinY, 0, cosY, 0},
		{0, 0, 0, 1}
	};
	mat4 z = {
		{cosZ, -sinZ, 0, 0},
		{sinZ, cosZ, 0, 0},
		{0, 0, 1, 0},
		{0, 0, 0, 1}
	};

	mat4_mul_mat4(x, y, x);
	mat4_mul_mat4(x, z, x);
	mat4_mul_vec3(x, v, out);
}
