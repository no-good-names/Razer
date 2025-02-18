//
// Created by cp176 on 1/25/2025.
//

#ifndef OBJECTS_H
#define OBJECTS_H

#include "math/maths.h"
#include "typedef.h"
#include "primitives.h"

typedef struct {
	v3_t *vertices;
	vec3 *vertices_m;
	iv3_t *triangles;
	ivec3 *triangles_m;
	int numVertices;
	int numTriangles;
	v3_t center;
	vec3 center_m;
	uint32_t *color;
	char name[32];
} Object_t;

typedef struct {
	float scale;
	v3_t rotation;
	vec3 rotation_m;
	v3_t translation;
	vec3 translation_m;
} Transformations_t;

typedef struct {
	Object_t object;
	Transformations_t transformations;
} Instance_t;

typedef struct {
	Instance_t *instances;
	int numInstances;
} Scene_t;

void ProjectToCanvas(iv2_t *dest, const v3_t v);

Object_t create_object(v3_t *vertices, iv3_t *triangles, int numVertices, int numTriangles, uint32_t *color);
void create_instance(Instance_t *dest, Object_t object, Transformations_t transformations);
Scene_t create_scene(Instance_t *instances, int numInstances);

void apply_transformation(Instance_t *instance, const Transformations_t translation);
void scale_object(Object_t object, float scale);
void rotate_object(Object_t object, v3_t rotation);

INLINE v3_t rotate_scene(v3_t v, v2_t rotation) {
	v = rotateX(v, rotation.x);
	v = rotateY(v, rotation.y);
	v = rotateZ(v, 0);
	return v;
}

void renderObject(const Object_t object);
void RenderScene(const Scene_t scene);

// vecs
void ProjectToCanvas_m(ivec2 *dest, const vec3 v);

Object_t create_object_m(vec3 *vertices, ivec3 *triangles, int numVertices, int numTriangles, uint32_t *color);
void create_instance_m(Instance_t *dest, Object_t object, Transformations_t transformations);
Scene_t create_scene_m(Instance_t *instances, int numInstances);

void apply_transformation_m(Instance_t *instance, const Transformations_t translation);
void scale_object_m(Object_t object, float scale);
void rotate_object_m(Object_t object, v3_t rotation);


INLINE void rotate_scene_m(vec3 v, vec3 rotation, vec3 out) {
	rotateX_m(v, rotation[0], out);
	rotateY_m(v, rotation[1], out);
	rotateZ_m(v, 0, out);

}

void renderObject_m(const Object_t object);
void RenderScene_m(const Scene_t scene);


#endif //OBJECTS_H
