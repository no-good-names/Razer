#ifndef VEC3_H
#define VEC3_H

#include <math.h>

typedef struct Vector3_t {
	float x, y, z;
} v3_t;

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

#endif