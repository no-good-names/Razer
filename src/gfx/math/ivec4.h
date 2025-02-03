#ifndef IVEC4_H
#define IVEC4_H

#include <stdint.h>

typedef struct IVector4 {
    int32_t x, y, z, w;
} iv4_t;

iv4_t iv4_add(iv4_t a, iv4_t b);
iv4_t iv4_sub(iv4_t a, iv4_t b);
iv4_t iv4_mul(iv4_t a, iv4_t b);
float iv4_dot(iv4_t a, iv4_t b);
float iv4_length(iv4_t a);
iv4_t iv4_normalize(iv4_t a);

// MISC CODE
iv4_t iv4_negate(iv4_t v);
iv4_t iv4_scale(iv4_t v, int s);

#endif