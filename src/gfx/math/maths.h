#ifndef MATHS_H

#include <stdint.h>
#include "vec2.h"
#include "vec3.h"
#include "vec4.h"
#include "ivec2.h"
#include "ivec3.h"
#include "ivec4.h"

#define PI		3.14159265358979323846264338327950288
#define PI_2	1.57079632679489661923132169163975144
#define PI_4	0.785398163397448309615660845819875721

#define DEG2RAD(deg) ((deg) * (PI / 180.0f))
#define RAD2DEG(rad) ((rad) * (180.0f / PI))

v3_t rotateX(v3_t v, float angle);
v3_t rotateY(v3_t v, float angle);
v3_t rotateZ(v3_t v, float angle);
#endif