#ifndef IVEC2_H
#define IVEC2_H

#include <stdint.h>

typedef struct {
    int32_t x, y;
} iv2_t;

typedef int32_t ivec2[2];

iv2_t iv2_add(iv2_t a, iv2_t b);
iv2_t iv2_sub(iv2_t a, iv2_t b);
iv2_t iv2_mul(iv2_t a, iv2_t b);
iv2_t iv2_cross(iv2_t a, iv2_t b);
float iv2_dot(iv2_t a, iv2_t b);
float iv2_length(iv2_t a);
iv2_t iv2_normalize(iv2_t a);

iv2_t iv2_negate(iv2_t v);
iv2_t iv2_scale(iv2_t v, int s);

INLINE void ivec2_add(ivec2 a, ivec2 b, ivec2 out) {
    out[0] = a[0] + b[0];
    out[1] = a[1] + b[1];
}

INLINE void ivec2_sub(ivec2 a, ivec2 b, ivec2 out) {
    out[0] = a[0] - b[0];
    out[1] = a[1] - b[1];
}

INLINE void ivec2_mul(ivec2 a, ivec2 b, ivec2 out) {
    out[0] = a[0] * b[0];
    out[1] = a[1] * b[1];
}

INLINE float ivec2_dot(ivec2 a, ivec2 b) {
    return a[0] * b[0] + a[1] * b[1];
}

INLINE float ivec2_length(ivec2 a) {
    return sqrtf(a[0] * a[0] + a[1] * a[1]);
}

INLINE void ivec2_normalize(ivec2 a, ivec2 out) {
    float length = ivec2_length(a);
    out[0] = a[0] / length;
    out[1] = a[1] / length;
}

INLINE void ivec2_negate(ivec2 v, ivec2 out) {
    out[0] = v[0] * -1;
    out[1] = v[1] * -1;
}

INLINE void ivec2_scale(ivec2 v, float s, ivec2 out) {
    out[0] = v[0] * s;
    out[1] = v[1] * s;
}

INLINE void ivec2_cpy(ivec2 a, ivec2 out) {
    out[0] = a[0];
    out[1] = a[1];
}

#endif