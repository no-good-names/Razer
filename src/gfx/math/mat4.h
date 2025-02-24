//
// Created by cp176 on 2/23/2025.
//

#ifndef MAT4_H
#define MAT4_H

#include "vec4.h"

typedef float mat4[4][4];

#define MAT4_IDENTITY_INIT { \
	{1, 0, 0, 0}, \
	{0, 1, 0, 0}, \
	{0, 0, 1, 0}, \
	{0, 0, 0, 1} \
}

#endif //MAT4_H
