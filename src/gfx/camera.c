//
// Created by cp176 on 1/25/2025.
//

#include "camera.h"

Camera_t g_camera = {0};

Camera_t create_camera(const v3_t position, const v2_t view_dir) {
	Camera_t camera = {
		.position = position,
		.view_dir = view_dir
	};
	return camera;
}

void update_camera(const Camera_t *camera) {
	g_camera = *camera;
	g_camera.position_m[0] = camera->position.x;
	g_camera.position_m[1] = camera->position.y;
	g_camera.position_m[2] = camera->position.z;
	g_camera.view_dir_m[0] = camera->view_dir.x;
	g_camera.view_dir_m[1] = camera->view_dir.y;
}
