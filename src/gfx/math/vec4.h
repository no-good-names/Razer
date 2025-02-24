#ifndef VEC4_H
#define VEC4_H

#include <math.h>

#include "../typedef.h"

typedef struct Vector4_t {
	float x, y, z, w;
} v4_t;

typedef float vec4[4];

v4_t v4_add(v4_t a, v4_t b);
v4_t v4_sub(v4_t a, v4_t b);
v4_t v4_mul(v4_t a, v4_t b);
float v4_dot(v4_t a, v4_t b);
float v4_length(v4_t a);
v4_t v4_normalize(v4_t a);

// MISC CODE

v4_t v4_negate(v4_t v);
v4_t v4_scale(v4_t v, float s);

INLINE void vec4_add(vec4 a, vec4 b, vec4 out) {
	out[0] = a[0] + b[0];
	out[1] = a[1] + b[1];
	out[2] = a[2] + b[2];
	out[3] = a[3] + b[3];
}
INLINE void vec4_sub(vec4 a, vec4 b, vec4 out) {
	out[0] = a[0] - b[0];
	out[1] = a[1] - b[1];
	out[2] = a[2] - b[2];
	out[3] = a[3] - b[3];
}
INLINE void vec4_mul(vec4 a, vec4 b, vec4 out) {
	out[0] = a[0] * b[0];
	out[1] = a[1] * b[1];
	out[2] = a[2] * b[2];
	out[3] = a[3] * b[3];
}
INLINE float vec4_dot(vec4 a, vec4 b) {
	return a[0] * b[0] + a[1] * b[1] + a[2] * b[2] + a[3] * b[3];
}
INLINE float vec4_length(vec4 a) {
	return sqrtf(a[0] * a[0] + a[1] * a[1] + a[2] * a[2] + a[3] * a[3]);
}
INLINE void vec4_normalize(vec4 a, vec4 out) {
	float length = vec4_length(a);
	out[0] = a[0] / length;
	out[1] = a[1] / length;
	out[2] = a[2] / length;
	out[3] = a[3] / length;
}
INLINE void vec4_negate(vec4 v, vec4 out) {
	out[0] = v[0] * -1;
	out[1] = v[1] * -1;
	out[2] = v[2] * -1;
	out[3] = v[3] * -1;
}
INLINE void vec4_scale(vec4 v, int s, vec4 out) {
	out[0] = v[0] * s;
	out[1] = v[1] * s;
	out[2] = v[2] * s;
	out[3] = v[3] * s;
}

#endif
