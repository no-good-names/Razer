//
// Created by cp176 on 1/25/2025.
//

#ifndef CAMERA_H
#define CAMERA_H

#include "math/maths.h"

typedef struct {
	vec3 position;
	vec3 view_dir;
} Camera_t;

extern Camera_t g_camera;

Camera_t create_camera(const vec3 position, const vec3 view_dir);
void move_camera(vec3 dir, vec3 pos);

#endif //CAMERA_H
