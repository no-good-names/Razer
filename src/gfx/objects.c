//
// Created by cp176 on 1/25/2025.
//

#include "objects.h"

#include <stdlib.h>
#include <string.h>

#include "camera.h"
#include "math/mat4.h"
#include "math/maths.h"
#include "math/vec3.h"

uint32_t draw_mode = LINE;

void ProjectToCanvas(ivec2 *dest, const vec3 v) {
    if (v[2] <= 0.0f) {
        return;
    }
    const float d = 1.0f; // depth
    // Perspective projection
    vec2 dv;
    dv[0] = (v[0] * d) / v[2];
    dv[1] = (v[1] * d) / v[2];

    // NOTE: THIS IS VIEWPORT TO CANVAS
    (*dest)[0] = dv[0] * (screen_size.x / aspect_ratio.x);
    (*dest)[1] = dv[1] * (screen_size.y / aspect_ratio.y);
}

Object_t create_object(vec3 *vertices, ivec3 *triangles, int numVertices, int numTriangles, uint32_t *color) {
	Object_t object = {
		.vertices = vertices,
		.triangles = triangles,
		.numVertices = numVertices,
		.numTriangles = numTriangles,
		.center = { 0, 0, 0 },
		.color = color
	};
	return object;
}

void create_instance(Instance_t *dest, const Object_t object, const Transformations_t transformations) {
	*dest = (Instance_t) {
		.object = object,
		.transformations = transformations
	};
	apply_transformation(dest, transformations);
}

Scene_t create_scene(Instance_t *instances, const int numInstances) {
	Scene_t scene = {
		.instances = instances,
		.numInstances = numInstances
	};
	return scene;
}

// TODO: scale and rotate from (0, 0, 0) then add the center then translate to the final position
void apply_transformation(Instance_t *instance, Transformations_t translation) {
	for (int i = 0; i < instance->object.numVertices; i++) {
		mat4_apply_transformation(instance->object.vertices[i], translation.scale, translation.rotation, translation.translation, instance->object.vertices[i]);
	}
}


void renderTriangle(ivec2 projected[3], uint32_t color) {
	switch (draw_mode) {
		case LINE:
			WireFrameTriangle(projected[0], projected[1], projected[2], color);
			break;
		case FILLED:
			FillTriangle(projected[0], projected[1], projected[2], color);
			break;
		default: break;
	}
}

// TODO: Fix shrinkage of object when rotating
void renderObject(Object_t object) {
    ivec2 projectedVertices[MAX_OBJECT_VERTICES];
    for (int i = 0; i < object.numVertices; i++) {
        vec3 tmp = {0};
        vec3_sub(object.center, g_camera.position, tmp);
        vec3_add(object.vertices[i], tmp, tmp);
        mat4_rotate_vec3(tmp, g_camera.view_dir, tmp);
        ProjectToCanvas(&projectedVertices[i], tmp);
    }
    for (int i = 0; i < object.numTriangles; i++) {
        ivec2 renderedTriangle[3];
    	ivec2_cpy(projectedVertices[object.triangles[i][0]], renderedTriangle[0]);
    	ivec2_cpy(projectedVertices[object.triangles[i][1]], renderedTriangle[1]);
    	ivec2_cpy(projectedVertices[object.triangles[i][2]], renderedTriangle[2]);
        renderTriangle(renderedTriangle, object.color[i]);
    }
}

void RenderScene(Scene_t scene) {
	for (int i = 0; i < scene.numInstances; i++) {
		renderObject(scene.instances[i].object);
	}
}
