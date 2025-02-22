//
// Created by cp176 on 1/25/2025.
//

#include "camera.h"

Camera_t g_camera = {0};

Camera_t create_camera(const vec3 position, const vec3 view_dir) {
	Camera_t camera = {
		.position = *position,
		.view_dir = *view_dir
	};
	return camera;
}

void move_camera(vec3 dir, vec3 pos) {
    vec3 new_position;
    vec3_add(g_camera.position, dir, new_position);
    vec3_add(new_position, pos, g_camera.position);
}
