#ifndef VEC4_H
#define VEC4_H

typedef struct Vector4_t {
	float x, y, z, w;
} v4_t;

v4_t v4_add(v4_t a, v4_t b);
v4_t v4_sub(v4_t a, v4_t b);
v4_t v4_mul(v4_t a, v4_t b);
float v4_dot(v4_t a, v4_t b);
float v4_length(v4_t a);
v4_t v4_normalize(v4_t a);

// MISC CODE

v4_t v4_negate(v4_t v);
v4_t v4_scale(v4_t v, float s);

#endif