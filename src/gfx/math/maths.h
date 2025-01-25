#ifndef MATHS_H
#define MATHS_H

#include <stdbool.h>

#include "../typedef.h"
#include <math.h>
#include <stdint.h>

/////////////// MATH DEFS ///////////////
#define PI 3.14159265358979323846
// Macros
#define DEG2RAD(deg) ((deg) * PI / 180.0f)
#define RAD2DEG(rad) ((rad) * 180.0f / PI)

typedef struct Vector2_t {
	float x, y;
} v2_t;

typedef struct IVector2_t {
	int32_t x, y;
} iv2_t;

typedef struct Vector3_t {
	float x, y, z;
} v3_t;

typedef struct IntVector3_t {
	int x, y, z;
} iv3_t;

typedef struct Vector4_t {
	float x, y, z, w;
} v4_t;

typedef struct Point_t {
	float x, y, z;
} Point_t;

#define MAT2_IDENTITY ((mat2_t){    \
{1, 0},                     \
{0, 1}})
#define MAT3_IDENTITY ((mat3_t){    \
{1, 0, 0},                  \
{0, 1, 0},                  \
{0, 0, 1}})
#define MAT4_IDENTITY ((mat4_t){    \
{1, 0, 0, 0},               \
{0, 1, 0, 0},               \
{0, 0, 1, 0},               \
{0, 0, 0, 1}})

typedef float mat2_t[2][2];
typedef float mat3_t[3][3];
typedef float mat4_t[4][4];
/////////////////////////////////////////

// VECTOR MATHS
v3_t v3_add(v3_t a, v3_t b);
v3_t v3_sub(v3_t a, v3_t b);
v3_t v3_mul(v3_t a, v3_t b);
v3_t v3_cross(v3_t a, v3_t b);
float v3_dot(v3_t a, v3_t b);
float v3_length(v3_t a);
v3_t v3_normalize(v3_t a);
float lerp(float a, float b, float t);
int *Interpolate(v2_t start, v2_t end);

bool isBigger(v2_t a, v2_t b);

#endif //MATHS_H
