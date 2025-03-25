//
// Created by cp176 on 2/21/2025.
//

#include "mat3.h"

#include "maths.h"


// x, y, z
// 1, 0, 0 [sx] -> [x', 0, 0]
// 0, 1, 0 [sy] -> [0, y', 0]
// 0, 0, 1 [1] 	-> [0, 	0, 1]

void mat3_scale(const mat3 m, const vec3 s, mat3 out) {
	out[0][0] = m[0][0] * s[0]; out[0][1] = m[0][1]; 		out[0][2] = m[0][2];
	out[1][0] = m[1][0]; 		out[1][1] = m[1][1] * s[1]; out[1][2] = m[1][2];
	out[2][0] = m[2][0]; 		out[2][1] = m[2][1]; 		out[2][2] = m[2][2] * s[2];
}


// x, y, z
// 1, 0, tx
// 0, 1, ty
// 0, 0, 1
void mat3_translate(const mat3 m, const vec3 t, mat3 out) {
	out[0][0] = m[0][0]; out[0][1] = m[0][1]; out[0][2] = m[0][2] + t[0]; // X: 1, 0, tx
	out[1][0] = m[1][0]; out[1][1] = m[1][1]; out[1][2] = m[1][2] + t[1]; // Y: 0, 1, yu
	out[2][0] = m[2][0]; out[2][1] = m[2][1]; out[2][2] = m[2][2];		  // Z: 0, 0, 1
}

// TODO: 3D matrix rotation
// ROT:
//	x,		y,		z
//	cosA,	-sinA,	0
//	sinA,	cosA,	0
//	0,		0,		1

void mat3_rotate(const mat3 m, const float rotation, mat3 out) {
	const float cosA = cosf(DEG2RAD(rotation));
	const float sinA = sinf(DEG2RAD(rotation));
	out[0][0] = cosA * m[0][0] - sinA * m[1][0];
	out[0][1] = cosA * m[0][1] - sinA * m[1][1];
	out[0][2] = cosA * m[0][2] - sinA * m[1][2];

	out[1][0] = sinA * m[0][0] + cosA * m[1][0];
	out[1][1] = sinA * m[0][1] + cosA * m[1][1];
	out[1][2] = sinA * m[0][2] + cosA * m[1][2];

	out[2][0] = m[2][0];
	out[2][1] = m[2][1];
	out[2][2] = m[2][2];
}

// @param t: transformation
// @param v: vector
// @param out: output vector
// void vec3_apply_transformation(Transform_2D_t t, vec3 v, vec3 out) {
// 	mat3 S, R, T, TRS;
// 	mat3_scale((mat3) MAT3_IDENTITY_INIT, t.scale, S);
// 	mat3_rotate((mat3) MAT3_IDENTITY_INIT, t.rotation, R);
// 	mat3_translate((mat3) MAT3_IDENTITY_INIT, t.translate, T);
// 	mat3_mul_mat3(S, R, TRS);
// 	mat3_mul_mat3(TRS, T, TRS);
// 	mat3_mul_vec3(TRS, v, out);
// }

