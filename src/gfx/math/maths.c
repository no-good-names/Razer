//
// Created by cp176 on 1/24/2025.
//

#include "maths.h"

#include <math.h>
#include <stdlib.h>

v2_t v2_sub(const v2_t a, const v2_t b) {
	return (v2_t) {
		.x = a.x - b.x,
		.y = a.y - b.y
	};
}

// add two vectors
v3_t v3_add(const v3_t a, const v3_t b) {
	return (v3_t) {
		.x = a.x + b.x,
		.y = a.y + b.y,
		.z = a.z + b.z
	};
}

v3_t v3_sub(const v3_t a, const v3_t b) {
	return (v3_t) {
		.x = a.x - b.x,
		.y = a.y - b.y,
		.z = a.z - b.z
	};
}

v3_t v3_mul(const v3_t a, const v3_t b) {
	return (v3_t) {
		.x = a.x * b.x,
		.y = a.y * b.y,
		.z = a.z * b.z
	};
}

v3_t v3_normalize(const v3_t a) {
	float length = sqrtf(a.x * a.x + a.y * a.y + a.z * a.z);
	return (v3_t) {
		.x = a.x / length,
		.y = a.y / length,
		.z = a.z / length
	};
}

v3_t v3_cross(const v3_t a, const v3_t b) {
	return (v3_t) {
		.x = a.y * b.z - a.z * b.y,
		.y = a.z * b.x - a.x * b.z,
		.z = a.x * b.y - a.y * b.x
	};
}

float v3_dot(const v3_t a, const v3_t b) {
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

float v3_length(v3_t a) {
	return sqrtf(a.x * a.x + a.y * a.y + a.z * a.z);
}

// B * t + A * (1-t)
float lerp(float a, float b, float t) {
	return a + t * (b - a);
}

v2_t v2_lerp(v2_t a, v2_t b, float t) {
	return (v2_t) {
		.x = lerp(a.x, b.x, t),
		.y = lerp(a.y, b.y, t)
	};
}

v2_t v2_add(v2_t a, float b) {
    return (v2_t) {
        .x = a.x + b,
        .y = a.y + b
    };
}

void mat4_translate(mat4x4_t matrix, const v3_t translation) {
	matrix[0][3] = translation.x;
	matrix[1][3] = translation.y;
	matrix[2][3] = translation.z;
}

v3_t v3_negate(const v3_t v) {
	return (v3_t) {
		.x = -v.x,
		.y = -v.y,
		.z = -v.z
	};
}

v2_t v2_negate(const v2_t v) {
    return (v2_t) {
        .x = v.x * -1,
        .y = v.y * -1
    };
}

v3_t rotateX(v3_t v, float angle) {
	float cosAngle = cosf(angle);
	float sinAngle = sinf(angle);
	return (v3_t) {
		.x = v.x * cosAngle - v.z * sinAngle,
		.y = v.y,
		.z = v.x * sinAngle + v.z * cosAngle
	};
}

v3_t rotateY(v3_t v, float angle) {
	float cosAngle = cosf(angle);
	float sinAngle = sinf(angle);
	return (v3_t) {
		.x = v.x,
		.y = v.y * cosAngle - v.z * sinAngle,
		.z = v.y * sinAngle + v.z * cosAngle
	};
}

v3_t rotateZ(v3_t v, float angle) {
	float cosAngle = cosf(angle);
	float sinAngle = sinf(angle);
	return (v3_t) {
		.x = v.x * cosAngle - v.y * sinAngle,
		.y = v.x * sinAngle + v.y * cosAngle,
		.z = v.z
	};
}

v3_t v3_scale(v3_t a, float scalar) {
    return (v3_t) {
        .x = a.x * scalar,
        .y = a.y * scalar,
        .z = a.z * scalar
    };
}
