//
// Created by cp176 on 1/25/2025.
//

#include "objects.h"
Object_t create_object(v3_t *vertices, iv3_t *triangles, int numVertices, int numTriangles, uint32_t *color) {
	Object_t object = {
		.vertices = vertices,
		.triangles = triangles,
		.numVertices = numVertices,
		.numTriangles = numTriangles,
		.color = color
	};
	return object;
}

Scene_t create_scene(Object_t *objects, int numObjects) {
	Scene_t scene = {
		.objects = objects,
		.numObjects = numObjects
	};
	return scene;
}

void transform_object(Object_t object, mat4_t transform) {
	for (int i = 0; i < object.numVertices; i++) {
		v4_t vertex = {object.vertices[i].x, object.vertices[i].y, object.vertices[i].z, 1.0f};
		v4_t transformed = {
			transform[0][0] * vertex.x + transform[0][1] * vertex.y + transform[0][2] * vertex.z + transform[0][3] * vertex.w,
			transform[1][0] * vertex.x + transform[1][1] * vertex.y + transform[1][2] * vertex.z + transform[1][3] * vertex.w,
			transform[2][0] * vertex.x + transform[2][1] * vertex.y + transform[2][2] * vertex.z + transform[2][3] * vertex.w,
			transform[3][0] * vertex.x + transform[3][1] * vertex.y + transform[3][2] * vertex.z + transform[3][3] * vertex.w
		};
		object.vertices[i] = (v3_t) {transformed.x, transformed.y, transformed.z};
	}
}
