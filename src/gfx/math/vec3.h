#ifndef VEC3_H
#define VEC3_H

#include <math.h>

typedef struct Vector3_t {
	float x, y, z;
} v3_t;

typedef float vec3[3];

v3_t v3_add(v3_t a, v3_t b);
v3_t v3_sub(v3_t a, v3_t b);
v3_t v3_mul(v3_t a, v3_t b);
v3_t v3_cross(v3_t a, v3_t b);
float v3_dot(v3_t a, v3_t b);
float v3_length(v3_t a);
v3_t v3_normalize(v3_t a);

// MISC CODE

v3_t v3_negate(v3_t v);
v3_t v3_scale(v3_t v, float s);

INLINE void vec3_add(vec3 a, vec3 b, vec3 out) {
	out[0] = a[0] + b[0];
	out[1] = a[1] + b[1];
	out[2] = a[2] + b[2];
}
INLINE void vec3_sub(vec3 a, vec3 b, vec3 out) {
	out[0] = a[0] - b[0];
	out[1] = a[1] - b[1];
	out[2] = a[2] - b[2];
}
INLINE void vec3_mul(vec3 a, vec3 b, vec3 out) {
	out[0] = a[0] * b[0];
	out[1] = a[1] * b[1];
	out[2] = a[2] * b[2];
}
INLINE float vec3_dot(vec3 a, vec3 b) {
	return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
}
INLINE float vec3_length(vec3 a) {
	return sqrtf(a[0] * a[0] + a[1] * a[1] + a[2] * a[2]);
}
INLINE void vec3_normalize(vec3 a, vec3 out) {
	float length = vec3_length(a);
	out[0] = a[0] / length;
	out[1] = a[1] / length;
	out[2] = a[2] / length;
}
INLINE void vec3_negate(vec3 v, vec3 out) {
	out[0] = v[0] * -1;
	out[1] = v[1] * -1;
	out[2] = v[2] * -1;
}
INLINE void vec3_scale(vec3 v, float s, vec3 out) {
	out[0] = v[0] * s;
	out[1] = v[1] * s;
	out[2] = v[2] * s;
}


#endif