#ifndef IVEC3_H
#define IVEC3_H

#include <stdint.h>
#include <math.h>

typedef struct iVector3_t {
    int32_t x, y, z;
} iv3_t;

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

#endif