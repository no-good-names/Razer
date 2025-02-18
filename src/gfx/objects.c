//
// Created by cp176 on 1/25/2025.
//

#include "objects.h"

#include <stdlib.h>
#include <string.h>

#include "camera.h"

void ProjectToCanvas(iv2_t *dest, const v3_t v) {
	if (v.z <= 0.0f) {
		return;
	}
	const float d = 1.0f; // depth
	// Perspective projection
	v2_t dv = {
		(v.x * d) / v.z,
		(v.y * d) / v.z
	};

	// NOTE: THIS IS VIEWPORT TO CANVAS
	*dest = (iv2_t) {
		.x = dv.x * (screen_size.x / aspect_ratio.x),
		.y = dv.y * (screen_size.y / aspect_ratio.y)
	};
}

Object_t create_object(v3_t *vertices, iv3_t *triangles, int numVertices, int numTriangles, uint32_t *color) {
	Object_t object = {
		.vertices = vertices,
		.triangles = triangles,
		.numVertices = numVertices,
		.numTriangles = numTriangles,
		.center = {0, 0, 0},
		.color = color
	};
	return object;
}

void create_instance(Instance_t *dest, Object_t object, Transformations_t transformations) {
	*dest = (Instance_t) {
		.object = object,
		.transformations = transformations
	};
	apply_transformation(dest, transformations);
}

Scene_t create_scene(Instance_t *instances, int numInstances) {
	Scene_t scene = {
		.instances = instances,
		.numInstances = numInstances
	};
	return scene;
}

v3_t scale_vertex(v3_t vertex, float scale) {
	return (v3_t) {
		.x = vertex.x * scale,
		.y = vertex.y * scale,
		.z = vertex.z * scale
	};
}

void rotate_object(const Object_t object, v3_t rotation) {
	if (rotation.x == 0 && rotation.y == 0 && rotation.z == 0) {
		return;
	}
	for (int i = 0; i < object.numVertices; i++) {
		object.vertices[i] = rotateX(object.vertices[i], rotation.x);
		object.vertices[i] = rotateY(object.vertices[i], rotation.y);
		object.vertices[i] = rotateZ(object.vertices[i], rotation.z);
	}
}


void renderTriangle(iv2_t projected[3], uint32_t color) {
#if RENDER_WIREFRAME == 1
	WireFrameTriangle(projected[0], projected[1], projected[2], color);
#else
	FillTriangle(projected[0], projected[1], projected[2], color);
#endif
}

void apply_transformation(Instance_t *instance, const Transformations_t translation) {
	for (int i = 0; i < instance->object.numVertices; i++) {
		instance->object.vertices[i] = rotateX(scale_vertex(instance->object.vertices[i], translation.scale), translation.rotation.x);
		instance->object.vertices[i] = rotateY(scale_vertex(instance->object.vertices[i], translation.scale), translation.rotation.y);
		instance->object.vertices[i] = rotateZ(scale_vertex(instance->object.vertices[i], translation.scale), translation.rotation.z);
	}
	instance->object.center = v3_add(instance->object.center, translation.translation);
}

void renderObject(const Object_t object) {
	iv2_t projectedVertices[MAX_OBJECT_VERTICES];
	for (int i = 0; i < object.numVertices; i++) {
		ProjectToCanvas(&projectedVertices[i], rotate_scene(v3_add(object.vertices[i],
			v3_sub(object.center, g_camera.position)), g_camera.view_dir));
	}
	for (int i = 0; i < object.numTriangles; i++) {
		iv2_t renderedTriangle[3] = {
			projectedVertices[object.triangles[i].x],
			projectedVertices[object.triangles[i].y],
			projectedVertices[object.triangles[i].z],
		};
		renderTriangle(renderedTriangle, object.color[i]);
	}
}

void RenderScene(const Scene_t scene) {
	for (int i = 0; i < scene.numInstances; i++) {
		renderObject(scene.instances[i].object);
	}
}


void ProjectToCanvas_m(ivec2 *dest, const vec3 v) {
	if (v[2] <= 0.0f) {
		return;
	}
	const float d = 1.0f; // depth
	// Perspective projection
	ivec2 dv;
	dv[0] =	(v[0] * d) / v[2];
	dv[1] =	(v[1] * d) / v[2];

	// NOTE: THIS IS VIEWPORT TO CANVAS
	*dest[0] = dv[0] * (screen_size.x / aspect_ratio.x);
	*dest[1] = dv[1] * (screen_size.y / aspect_ratio.y);
}

Object_t create_object_m(vec3 *vertices, ivec3 *triangles, int numVertices, int numTriangles, uint32_t *color) {
	Object_t object = {
		.vertices_m = vertices,
		.triangles_m = triangles,
		.numVertices = numVertices,
		.numTriangles = numTriangles,
		.center_m = { 0, 0, 0 },
		.color = color
	};
	return object;
}
void create_instance_m(Instance_t *dest, Object_t object, Transformations_t transformations) {
	*dest = (Instance_t) {
		.object = object,
		.transformations = transformations
	};
	apply_transformation_m(dest, transformations);
}

Scene_t create_scene_m(Instance_t *instances, int numInstances);

void apply_transformation_m(Instance_t *instance, Transformations_t translation) {
	for (int i = 0; i < instance->object.numVertices; i++) {
		vec3_scale(instance->object.vertices_m[i], translation.scale, instance->object.vertices_m[i]);
		rotate_m(instance->object.vertices_m[i], translation.rotation_m, instance->object.vertices_m[i]);
	}
	vec3_add(instance->object.center_m, translation.translation_m, instance->object.center_m);
}

void renderTriangle_m(ivec2 projected[3], uint32_t color) {
	WireFrameTriangle_m(projected[0], projected[1], projected[2], color);
}

void renderObject_m(Object_t object) {
	ivec2 projectedVertices[MAX_OBJECT_VERTICES];
	for (int i = 0; i < object.numVertices; i++) {
		vec3 tmp;
		vec3_sub(object.center_m, g_camera.position_m, tmp);
		vec3_add(object.vertices_m[i], tmp, tmp);
		rotate_scene_m(tmp, g_camera.view_dir_m, tmp);
		ProjectToCanvas_m(&projectedVertices[i], tmp);
	}
	for (int i = 0; i < object.numTriangles; i++) {
		ivec2 renderedTriangle[3] = {0};
		ivec2_cpy(renderedTriangle[0], projectedVertices[object.triangles_m[i][0]]);
		ivec2_cpy(renderedTriangle[1], projectedVertices[object.triangles_m[i][1]]);
		ivec2_cpy(renderedTriangle[2], projectedVertices[object.triangles_m[i][2]]);

		renderTriangle_m(renderedTriangle, object.color[i]);
	}
}
