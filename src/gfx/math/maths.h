#ifndef MATHS_H
#define MATHS_H

#include <stdint.h>
#include "vec2.h"
#include "vec3.h"
#include "vec4.h"
#include "ivec2.h"
#include "ivec3.h"
#include "ivec4.h"
#include "mat3.h"
#include "mat4.h"

#define PI		3.14159265358979323846264338327950288
#define PI_2	1.57079632679489661923132169163975144
#define PI_4	0.785398163397448309615660845819875721

#define DEG2RAD(deg) ((deg) * (PI / 180.0f))
#define RAD2DEG(rad) ((rad) * (180.0f / PI))

typedef struct {
	vec3 scale;
	vec3 rotation; // rotate on x, y, z axis
	vec3 translation;
} Transformations_t;

INLINE void LinearInterpolate(vec2 a, vec2 b, const float t, vec2 out) {
    out[0] = a[0] + (b[0] - a[0]) * t;
    out[1] = a[1] + (b[1] - a[1]) * t;
}

INLINE void rotate_x_axis(vec3 v, float angle, vec3 out) {
	const float cos = cosf(DEG2RAD(angle));
	const float sin = sinf(DEG2RAD(angle));
	const mat4 m = {
		{1, 0, 0, 0},
		{0, cos, -sin, 0},
		{0, sin, cos, 0},
		{0, 0, 0, 1}
	};
	vec3 tmp;
	out[0] = v[0];
	out[1] = v[0] * m[0][1] + v[1] * m[1][1] + v[2] * m[2][1] + m[1][3];
	out[2] = v[0] * m[0][2] + v[1] * m[1][2] + v[2] * m[2][2] + m[2][3];
}

INLINE void rotate_y_axis(vec3 v, float angle, vec3 out) {
	const float cos = cosf(DEG2RAD(angle));
	const float sin = sinf(DEG2RAD(angle));
	const mat4 m = {
		{cos, 0, sin, 0},
		{0, 1, 0, 0},
		{-sin, 0, cos, 0},
		{0, 0, 0, 1}
	};
	vec3 tmp;
	tmp[0] = v[0] * m[0][0] + v[1] * m[0][1] + v[2] * m[0][2] + m[0][3];
	tmp[1] = v[0] * m[1][0] + v[1] * m[1][1] + v[2] * m[1][2] + m[1][3];
	tmp[2] = v[0] * m[2][0] + v[1] * m[2][1] + v[2] * m[2][2] + m[2][3];
	vec3_cpy(tmp, out);
}

INLINE void rotate_z_axis(vec3 v, float angle, vec3 out) {
	const float cos = cosf(DEG2RAD(angle));
	const float sin = sinf(DEG2RAD(angle));
	const mat4 m = {
		{cos, -sin, 0, 0},
		{sin, cos, 0, 0},
		{0, 0, 1, 0},
		{0, 0, 0, 1}
	};
	vec3 tmp;
	tmp[0] = v[0] * m[0][0] + v[1] * m[0][1] + v[2] * m[0][2] + m[0][3];
	tmp[1] = v[0] * m[1][0] + v[1] * m[1][1] + v[2] * m[1][2] + m[1][3];
	tmp[2] = v[0] * m[2][0] + v[1] * m[2][1] + v[2] * m[2][2] + m[2][3];
	vec3_cpy(tmp, out);
}

#endif