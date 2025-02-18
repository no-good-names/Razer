//
// Created by cp176 on 1/25/2025.
//

#include "objects.h"

#include <stdlib.h>
#include <string.h>

#include "camera.h"

void ProjectToCanvas(ivec2 *dest, const vec3 v) {
    if (v[2] <= 0.0f) {
        printf("Vertex is behind the camera\n");
        return;
    }
    const float d = 1.0f; // depth
    // Perspective projection
    ivec2 dv;
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

void renderTriangle(ivec2 projected[3], uint32_t color) {
	WireFrameTriangle(projected[0], projected[1], projected[2], color);
}


void apply_transformation(Instance_t *instance, Transformations_t translation) {
    for (int i = 0; i < instance->object.numVertices; i++) {
        vec3 scaled_vertex;
        vec3_scale(instance->object.vertices[i], translation.scale, scaled_vertex);

        vec3 rotated_vertex;
        rotateX(scaled_vertex, translation.rotation[0], rotated_vertex);
        rotateY(rotated_vertex, translation.rotation[1], rotated_vertex);
        rotateZ(rotated_vertex, translation.rotation[2], rotated_vertex);

        vec3_cpy(instance->object.vertices[i], rotated_vertex);
    }
    vec3_add(instance->object.center, translation.translation, instance->object.center);
}

void renderObject(Object_t object) {
    ivec2 projectedVertices[MAX_OBJECT_VERTICES];
    for (int i = 0; i < object.numVertices; i++) {
        vec3 tmp = {0};
    	printf("vertex: %d\n", i);
        vec3_sub(object.center, g_camera.position, tmp);
    	printf("step 1 tmp: %f %f %f\n", tmp[0], tmp[1], tmp[2]);
        vec3_add(object.vertices[i], tmp, tmp);
    	printf("step 2 tmp: %f %f %f\n", tmp[0], tmp[1], tmp[2]);
        rotate_m(tmp, g_camera.view_dir, tmp);
    	printf("step 3 tmp: %f %f %f\n", tmp[0], tmp[1], tmp[2]);
        ProjectToCanvas(&projectedVertices[i], tmp);
    }
    for (int i = 0; i < object.numTriangles; i++) {
        ivec2 renderedTriangle[3];
    	ivec2_cpy(renderedTriangle[0], projectedVertices[object.triangles[i][0]]);
    	ivec2_cpy(renderedTriangle[1], projectedVertices[object.triangles[i][1]]);
    	ivec2_cpy(renderedTriangle[2], projectedVertices[object.triangles[i][2]]);
        renderTriangle(renderedTriangle, object.color[i]);
    }
}

void RenderScene(Scene_t scene) {
	for (int i = 0; i < scene.numInstances; i++) {
		renderObject(scene.instances[i].object);
	}
}
