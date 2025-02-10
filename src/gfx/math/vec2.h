#ifndef VEC2_H
#define VEC2_H
#include <math.h>
// #include <simde/x86/sse.h>
#include "../typedef.h"

typedef struct {
    float x, y;
} v2_t;

typedef float vec2[2];

v2_t v2_add(v2_t a, v2_t b);
v2_t v2_sub(v2_t a, v2_t b);
v2_t v2_mul(v2_t a, v2_t b);
float v2_dot(v2_t a, v2_t b);
float v2_length(v2_t a);
v2_t v2_normalize(v2_t a);

v2_t v2_negate(v2_t v);
v2_t v2_scale(v2_t v, float s);

// SIMD example
// INLINE void vec2_add(vec2 a, vec2 b, vec2 out) {
//     const simde__m128 va = simde_mm_loadu_ps(a);
//     const simde__m128 vb = simde_mm_loadu_ps(b);
//     const simde__m128 v_out = simde_mm_add_ps(va, vb);
//     simde_mm_storeu_ps(out, v_out);
// }

INLINE void vec2_add(vec2 a, vec2 b, vec2 out) {
    out[0] = a[0] + b[0];
    out[1] = a[1] + b[1];
}

INLINE void vec2_sub(vec2 a, vec2 b, vec2 out) {
    out[0] = a[0] - b[0];
    out[1] = a[1] - b[1];
}

INLINE void vec2_mul(vec2 a, vec2 b, vec2 out) {
    out[0] = a[0] * b[0];
    out[1] = a[1] * b[1];
}

INLINE float vec2_dot(vec2 a, vec2 b) {
    return a[0] * b[0] + a[1] * b[1];
}

INLINE float vec2_length(vec2 a) {
    return sqrtf(a[0] * a[0] + a[1] * a[1]);
}

INLINE void vec2_normalize(vec2 a, vec2 out) {
    float length = vec2_length(a);
    out[0] = a[0] / length;
    out[1] = a[1] / length;
}

INLINE void vec2_negate(vec2 v, vec2 out) {
    out[0] = v[0] * -1;
    out[1] = v[1] * -1;
}

INLINE void vec2_scale(vec2 v, float s, vec2 out) {
    out[0] = v[0] * s;
    out[1] = v[1] * s;
}

#endif