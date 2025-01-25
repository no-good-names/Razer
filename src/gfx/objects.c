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
// TODO: Add transformations
