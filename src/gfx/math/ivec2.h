#ifndef IVEC2_H
#define IVEC2_H

#include <stdint.h>

typedef struct {
    int32_t x, y, z;
} iv2_t;

iv2_t iv2_add(iv2_t a, iv2_t b);
iv2_t iv2_sub(iv2_t a, iv2_t b);
iv2_t iv2_mul(iv2_t a, iv2_t b);
iv2_t iv2_cross(iv2_t a, iv2_t b);
float iv2_dot(iv2_t a, iv2_t b);
float iv2_length(iv2_t a);
iv2_t iv2_normalize(iv2_t a);

iv2_t iv2_negate(iv2_t v);
iv2_t iv2_scale(iv2_t v, int s);

#endif