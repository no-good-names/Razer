//
// Created by cp176 on 1/24/2025.
//

#include "maths.h"

#include <math.h>
#include <stdlib.h>

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
