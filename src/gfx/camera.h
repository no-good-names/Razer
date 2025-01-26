//
// Created by cp176 on 1/25/2025.
//

#ifndef CAMERA_H
#define CAMERA_H

#include "objects.h"
#include "math/maths.h"

typedef struct {
	v3_t position;
	v3_t view_dir;
} Camera_t;

Camera_t create_camera(v3_t position, v3_t view_dir);

#endif //CAMERA_H
