//
// Created by cp176 on 4/3/2025.
//

#ifndef OBJECT_H
#define OBJECT_H

#include "math/maths.h"

typedef struct {
	vec3 *vertices;
	ivec3 *indices;
	uint32_t *colors;
	unsigned int num_vertices;
	unsigned int num_indices;
} Object_t;

typedef struct {
	Object_t object;
	Transformations_t transformations;
} Instance_t;

Object_t CreateObject(vec3 vertices[], ivec3 indices[], uint32_t *colors, unsigned int num_vertices, unsigned int num_indices);
Instance_t CreateInstance(const Object_t object, vec3 translation, vec3 rotation, vec3 scale);

void RenderObject(Object_t object);
void ApplyTransformations(vec3 v, const Transformations_t transformations, vec3 out);
void RenderInstance(Instance_t instance);

#endif //OBJECT_H
