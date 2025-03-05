//
// Created by cp176 on 2/21/2025.
//

#ifndef MAT3_H
#define MAT3_H

#include "vec3.h"

typedef float mat3[3][3];

#define MAT3_IDENTITY_INIT { \
	{1, 0, 0}, \
	{0, 1, 0}, \
	{0, 0, 1} \
}

INLINE void mat3_mul_vec3(const mat3 m, const vec3 v, vec3 out) {
	out[0]=v[0]*m[0][0] + v[1]*m[0][1] + v[2]*m[0][2];
	out[1]=v[0]*m[1][0] + v[1]*m[1][1] + v[2]*m[1][2];
	out[2]=v[0]*m[2][0] + v[1]*m[2][1] + v[2]*m[2][2];
}

INLINE void mat3_mul_mat3(const mat3 a, const mat3 b, mat3 out) {
	out[0][0] = a[0][0]*b[0][0] + a[0][1]*b[1][0] + a[0][2]*b[2][0];
	out[0][1] = a[0][0]*b[0][1] + a[0][1]*b[1][1] + a[0][2]*b[2][1];
	out[0][2] = a[0][0]*b[0][2] + a[0][1]*b[1][2] + a[0][2]*b[2][2];

	out[1][0] = a[1][0]*b[0][0] + a[1][1]*b[1][0] + a[1][2]*b[2][0];
	out[1][1] = a[1][0]*b[0][1] + a[1][1]*b[1][1] + a[1][2]*b[2][1];
	out[1][2] = a[1][0]*b[0][2] + a[1][1]*b[1][2] + a[1][2]*b[2][2];

	out[2][0] = a[2][0]*b[0][0] + a[2][1]*b[1][0] + a[2][2]*b[2][0];
	out[2][1] = a[2][0]*b[0][1] + a[2][1]*b[1][1] + a[2][2]*b[2][1];
	out[2][2] = a[2][0]*b[0][2] + a[2][1]*b[1][2] + a[2][2]*b[2][2];
}

void mat3_scale(const mat3 m, const vec3 s, mat3 out);
void mat3_translate(const mat3 m, const vec3 t, mat3 out);
void mat3_rotate(const mat3 m, const float rotation, mat3 out);
// void vec3_apply_transformation(Transform_2D_t t, vec3 v, vec3 out);


#endif //MAT3_H
