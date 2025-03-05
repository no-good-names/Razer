//
// Created by cp176 on 1/25/2025.
//

#ifndef OBJECTS_H
#define OBJECTS_H

#include "math/maths.h"
#include "typedef.h"
#include "primitives.h"

static enum {
	LINE = 0,
	FILLED = 1
} DrawMode;

extern uint32_t draw_mode;

typedef struct {
	vec3 *vertices;
	ivec3 *triangles;
	int numVertices;
	int numTriangles;
	vec3 center;
	uint32_t *color;
	char name[32];
} Object_t;

typedef struct {
	Object_t object;
	Transformations_t transformations;
} Instance_t;

typedef struct {
	Instance_t *instances;
	int numInstances;
} Scene_t;

INLINE void SetDrawMode(uint32_t mode) {
	draw_mode = mode;
}

// vecs
void ProjectToCanvas(ivec2 *dest, const vec3 v);

Object_t create_object(vec3 *vertices, ivec3 *triangles, int numVertices, int numTriangles, uint32_t *color);
void create_instance(Instance_t *dest, Object_t object, Transformations_t transformations);
Scene_t create_scene(Instance_t *instances, int numInstances);

void apply_transformation(Instance_t *instance, const Transformations_t translation);

void renderObject(Object_t object);
void RenderScene(Scene_t scene);


#endif //OBJECTS_H
