//
// Created by cp176 on 1/25/2025.
//

#include "camera.h"

Camera_t create_camera(v3_t position, v3_t view_dir) {
	Camera_t camera = {
		.position = position,
		.view_dir = view_dir
	};
	return camera;
}
