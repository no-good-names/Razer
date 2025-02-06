#ifndef VEC2_H
#define VEC2_H

typedef struct {
    float x, y;
} v2_t;

v2_t v2_add(v2_t a, v2_t b);
v2_t v2_sub(v2_t a, v2_t b);
v2_t v2_mul(v2_t a, v2_t b);
float v2_dot(v2_t a, v2_t b);
float v2_length(v2_t a);
v2_t v2_normalize(v2_t a);

v2_t v2_negate(v2_t v);
v2_t v2_scale(v2_t v, float s);

#endif