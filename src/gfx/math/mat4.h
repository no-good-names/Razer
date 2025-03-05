//
// Created by cp176 on 2/23/2025.
//

#ifndef MAT4_H
#define MAT4_H

#include <stdint.h>

#include "vec3.h"
#include "vec4.h"

typedef float mat4[4][4];

#define MAT4_IDENTITY_INIT { \
	{1, 0, 0, 0}, \
	{0, 1, 0, 0}, \
	{0, 0, 1, 0}, \
	{0, 0, 0, 1} \
}

INLINE void mat4_mul_vec3(const mat4 m, const vec3 v, vec3 out) {
	out[0] = v[0]*m[0][0] + v[1]*m[0][1] + v[2]*m[0][2] + m[0][3];
	out[1] = v[0]*m[1][0] + v[1]*m[1][1] + v[2]*m[1][2] + m[1][3];
	out[2] = v[0]*m[2][0] + v[1]*m[2][1] + v[2]*m[2][2] + m[2][3];
}

INLINE void mat4_mul_mat4(const mat4 a, const mat4 b, mat4 out) {
	out[0][0] = a[0][0]*b[0][0] + a[0][1]*b[1][0] + a[0][2]*b[2][0] + a[0][3]*b[3][0];
	out[0][1] = a[0][0]*b[0][1] + a[0][1]*b[1][1] + a[0][2]*b[2][1] + a[0][3]*b[3][1];
	out[0][2] = a[0][0]*b[0][2] + a[0][1]*b[1][2] + a[0][2]*b[2][2] + a[0][3]*b[3][2];
	out[0][3] = a[0][0]*b[0][3] + a[0][1]*b[1][3] + a[0][2]*b[2][3] + a[0][3]*b[3][3];

	out[1][0] = a[1][0]*b[0][0] + a[1][1]*b[1][0] + a[1][2]*b[2][0] + a[1][3]*b[3][0];
	out[1][1] = a[1][0]*b[0][1] + a[1][1]*b[1][1] + a[1][2]*b[2][1] + a[1][3]*b[3][1];
	out[1][2] = a[1][0]*b[0][2] + a[1][1]*b[1][2] + a[1][2]*b[2][2] + a[1][3]*b[3][2];
	out[1][3] = a[1][0]*b[0][3] + a[1][1]*b[1][3] + a[1][2]*b[2][3] + a[1][3]*b[3][3];

	out[2][0] = a[2][0]*b[0][0] + a[2][1]*b[1][0] + a[2][2]*b[2][0] + a[2][3]*b[3][0];
	out[2][1] = a[2][0]*b[0][1] + a[2][1]*b[1][1] + a[2][2]*b[2][1] + a[2][3]*b[3][1];
	out[2][2] = a[2][0]*b[0][2] + a[2][1]*b[1][2] + a[2][2]*b[2][2] + a[2][3]*b[3][2];
	out[2][3] = a[2][0]*b[0][3] + a[2][1]*b[1][3] + a[2][2]*b[2][3] + a[2][3]*b[3][3];

	out[3][0] = a[3][0]*b[0][0] + a[3][1]*b[1][0] + a[3][2]*b[2][0] + a[3][3]*b[3][0];
	out[3][1] = a[3][0]*b[0][1] + a[3][1]*b[1][1] + a[3][2]*b[2][1] + a[3][3]*b[3][1];
	out[3][2] = a[3][0]*b[0][2] + a[3][1]*b[1][2] + a[3][2]*b[2][2] + a[3][3]*b[3][2];
	out[3][3] = a[3][0]*b[0][3] + a[3][1]*b[1][3] + a[3][2]*b[2][3] + a[3][3]*b[3][3];
}

INLINE void vec3_to_mat4(const vec3 v, mat4 out) {
	out = (mat4) {
		{v[0], 0, 0, 0},
		{0, v[1], 0, 0},
		{0, 0, v[2], 0},
		{0, 0, 0,	1}
	};
}

void mat4_scale(const mat4 m, const vec3 s, mat4 out);
void mat4_translate(const mat4 m, const vec3 t, mat4 out);
void mat4_rotate(const mat4 v, const vec3 rotation, mat4 out);
void mat4_rotate_vec3(const vec3 v, const vec3 rotation, vec3 out);
INLINE void mat4_apply_transformation(vec3 v, const vec3 scale, const vec3 rotation, const vec3 translation, vec3 out) {
	mat4 S, R, T, TRS;
	mat4_scale((mat4) MAT4_IDENTITY_INIT, scale, S);
	mat4_rotate((mat4) MAT4_IDENTITY_INIT, rotation, R);
	mat4_translate((mat4) MAT4_IDENTITY_INIT, translation, T);
	mat4_mul_mat4(T, R, TRS);
	mat4_mul_mat4(TRS, S, TRS);
	mat4_mul_vec3(TRS, v, out);
}

#endif //MAT4_H
