#ifndef IVEC3_H
#define IVEC3_H

#include <stdint.h>
#include <math.h>

typedef struct iVector3_t {
    int32_t x, y, z;
} iv3_t;

typedef int ivec3[3];

iv3_t iv3_add(iv3_t a, iv3_t b);
iv3_t iv3_sub(iv3_t a, iv3_t b);
iv3_t iv3_mul(iv3_t a, iv3_t b);
iv3_t iv3_cross(iv3_t a, iv3_t b);
float iv3_dot(iv3_t a, iv3_t b);
float iv3_length(iv3_t a);
iv3_t iv3_normalize(iv3_t a);

// MISC CODE

iv3_t iv3_negate(iv3_t v);
iv3_t iv3_scale(iv3_t v, int s);

INLINE void ivec3_add(ivec3 a,ivec3 b, ivec3 out) {
    out[0] = a[0] + b[0];
    out[1] = a[1] + b[1];
    out[2] = a[2] + b[2];
}
INLINE void ivec3_sub(ivec3 a, ivec3 b, ivec3 out) {
    out[0] = a[0] - b[0];
    out[1] = a[1] - b[1];
    out[2] = a[2] - b[2];
}
INLINE void ivec3_mul(ivec3 a, ivec3 b, ivec3 out) {
    out[0] = a[0] * b[0];
    out[1] = a[1] * b[1];
    out[2] = a[2] * b[2];
    out[3] = a[3] * b[3];
}
INLINE float ivec3_dot(ivec3 a, ivec3 b) {
    return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
}
INLINE float ivec3_length(ivec3 a) {
    return sqrtf(a[0] * a[0] + a[1] * a[1] + a[2] * a[2]);
}
INLINE void ivec3_normalize(ivec3 a, ivec3 out) {
    float length = ivec3_length(a);
    out[0] = a[0] / length;
    out[1] = a[1] / length;
    out[2] = a[2] / length;
}
INLINE void ivec3_negate(ivec3 v, ivec3 out) {
    out[0] = v[0] * -1;
    out[1] = v[1] * -1;
    out[2] = v[2] * -1;
    out[3] = v[3] * -1;
}
INLINE void ivec3_scale(ivec3 v, int s, ivec3 out) {
    out[0] = v[0] * s;
    out[1] = v[1] * s;
    out[2] = v[2] * s;
    out[3] = v[3] * s;
}

#endif