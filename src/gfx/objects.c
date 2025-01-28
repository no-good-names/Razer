//
// Created by cp176 on 1/25/2025.
//

#include "objects.h"

#include <stdlib.h>
#include <string.h>

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

void apply_transformation(Instance_t *instance, const Transformations_t translation) {
	if (translation.rotation.x == 0 && translation.rotation.y == 0 && translation.rotation.z == 0) {
		return;
	}
	for (int i = 0; i < instance->object.numVertices; i++) {
		instance->object.vertices[i] = rotateX(scale_vertex(instance->object.vertices[i], translation.scale), translation.rotation.x);
		instance->object.vertices[i] = rotateY(scale_vertex(instance->object.vertices[i], translation.scale), translation.rotation.y);
		instance->object.vertices[i] = rotateZ(scale_vertex(instance->object.vertices[i], translation.scale), translation.rotation.z);
	}
	instance->object.center = v3_add(instance->object.center, translation.translation);
}



