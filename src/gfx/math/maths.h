#ifndef MATHS_H

#include <stdint.h>
#include "vec2.h"
#include "vec3.h"
#include "vec4.h"
#include "ivec2.h"
#include "ivec3.h"
#include "ivec4.h"

#define PI 3.14159265358979323846

#define DEG2RAD(deg) ((deg) * PI / 180.0f)
#define RAD2DEG(rad) ((rad) * 180.0f / PI)

v3_t rotateX(v3_t v, float angle);
v3_t rotateY(v3_t v, float angle);
v3_t rotateZ(v3_t v, float angle);
#endif