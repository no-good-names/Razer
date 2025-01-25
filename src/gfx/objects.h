//
// Created by cp176 on 1/25/2025.
//

#ifndef OBJECTS_H
#define OBJECTS_H

#include "math/maths.h"
#include "typedef.h"
#include "prim.h"

typedef struct {
	v3_t *vertices;
	iv3_t *triangles;
	int numVertices;
	int numTriangles;
	uint32_t *color;
} Object_t;

typedef struct {
	Object_t *objects;
	int numObjects;
} Scene_t;

Object_t create_object(v3_t *vertices, iv3_t *triangles, int numVertices, int numTriangles, uint32_t *color);
Scene_t create_scene(Object_t *objects, int numObjects);

void transform_object(Object_t object, mat4_t transform);

#endif //OBJECTS_H
