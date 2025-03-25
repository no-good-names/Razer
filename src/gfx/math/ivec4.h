#ifndef IVEC4_H
#define IVEC4_H

#include <stdint.h>
#include <math.h>
#include "../typedef.h"

typedef struct IVector4 {
    int32_t x, y, z, w;
} iv4_t;

typedef int32_t ivec4[4];

iv4_t iv4_add(iv4_t a, iv4_t b);
iv4_t iv4_sub(iv4_t a, iv4_t b);
iv4_t iv4_mul(iv4_t a, iv4_t b);
float iv4_dot(iv4_t a, iv4_t b);
float iv4_length(iv4_t a);
iv4_t iv4_normalize(iv4_t a);

// MISC CODE
iv4_t iv4_negate(iv4_t v);
iv4_t iv4_scale(iv4_t v, int s);

INLINE void ivec4_add(ivec4 a, ivec4 b, ivec4 out) {
    out[0] = a[0] + b[0];
    out[1] = a[1] + b[1];
    out[2] = a[2] + b[2];
    out[3] = a[3] + b[3];
}
INLINE void ivec4_sub(ivec4 a, ivec4 b, ivec4 out) {
    out[0] = a[0] - b[0];
    out[1] = a[1] - b[1];
    out[2] = a[2] - b[2];
    out[3] = a[3] - b[3];
}
INLINE void ivec4_mul(ivec4 a, ivec4 b, ivec4 out) {
    out[0] = a[0] * b[0];
    out[1] = a[1] * b[1];
    out[2] = a[2] * b[2];
    out[3] = a[3] * b[3];
}
INLINE float ivec4_dot(ivec4 a, ivec4 b) {
    return a[0] * b[0] + a[1] * b[1] + a[2] * b[2] + a[3] * b[3];
}
INLINE float ivec4_length(ivec4 a) {
    return sqrtf(a[0] * a[0] + a[1] * a[1] + a[2] * a[2] + a[3] * a[3]);
}
INLINE void ivec4_normalize(ivec4 a, ivec4 out) {
    float length = ivec4_length(a);
    out[0] = a[0] / length;
    out[1] = a[1] / length;
    out[2] = a[2] / length;
    out[3] = a[3] / length;
}
INLINE void ivec4_negate(ivec4 v, ivec4 out) {
    out[0] = v[0] * -1;
    out[1] = v[1] * -1;
    out[2] = v[2] * -1;
    out[3] = v[3] * -1;
}
INLINE void ivec4_scale(ivec4 v, int s, ivec4 out) {
    out[0] = v[0] * s;
    out[1] = v[1] * s;
    out[2] = v[2] * s;
    out[3] = v[3] * s;
}

#endif