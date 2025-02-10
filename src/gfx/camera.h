//
// Created by cp176 on 1/25/2025.
//

#ifndef CAMERA_H
#define CAMERA_H

#include "objects.h"
#include "math/maths.h"

typedef struct {
	v3_t position;
	v2_t view_dir;
	float *z_buffer;
} Camera_t;

extern Camera_t g_camera;

Camera_t create_camera(v3_t position, v2_t view_dir);
void update_camera(const Camera_t *camera);

#endif //CAMERA_H
