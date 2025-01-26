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

typedef float mat2x2_t[2][2];
typedef float mat3x3_t[3][3];
typedef float mat4x4_t[4][4];

#define MAT2_IDENTITY ((mat2x2_t){    \
{1, 0},                     \
{0, 1}})
#define MAT3_IDENTITY ((mat3x3_t){    \
{1, 0, 0},                  \
{0, 1, 0},                  \
{0, 0, 1}})
#define MAT4_IDENTITY ((mat4x4_t){    \
{1, 0, 0, 0},               \
{0, 1, 0, 0},               \
{0, 0, 1, 0},               \
{0, 0, 0, 1}})

/////////////////////////////////////////

// VECTOR MATHS
v2_t v2_sub(const v2_t a, const v2_t b);

v3_t v3_add(v3_t a, v3_t b);
v3_t v3_sub(v3_t a, v3_t b);
v3_t v3_mul(v3_t a, v3_t b);
v3_t v3_cross(v3_t a, v3_t b);
float v3_dot(v3_t a, v3_t b);
float v3_length(v3_t a);
v3_t v3_normalize(v3_t a);
float lerp(float a, float b, float t);
int *Interpolate(v2_t start, v2_t end);

// MATRIX MATHS
void mat2_mul(mat2x2_t a, mat2x2_t b, mat2x2_t result);
void mat3_mul(mat3x3_t a, mat3x3_t b, mat3x3_t result);
void mat4_mul(mat4x4_t a, mat4x4_t b, mat4x4_t result);
void mat4_translate(mat4x4_t matrix, v3_t translation);
void mat4_scale(mat4x4_t matrix, v3_t scale);
void mat4_rotate(mat4x4_t matrix, float angle, v3_t axis);
void mat4_perspective(mat4x4_t matrix, float fov, float aspect, float near, float far);

#endif //MATHS_H
