//
// Created by cp176 on 4/3/2025.
//

#include "object.h"

#include "primitives.h"
#include "window.h"

Object_t CreateObject(vec3 vertices[], ivec3 indices[], uint32_t *colors, unsigned int num_vertices, unsigned int num_indices) {
	Object_t object;
	object.vertices = vertices;
	object.indices = indices;
	object.colors = colors;
	object.num_vertices = num_vertices;
	object.num_indices = num_indices;
	return object;
}

Instance_t CreateInstance(const Object_t object, vec3 translation, vec3 rotation, vec3 scale) {
	Instance_t instance;
	instance.object = object;
	vec3_cpy(translation, instance.transformations.translation);
	vec3_cpy(rotation, instance.transformations.rotation);
	vec3_cpy(scale, instance.transformations.scale);
	return instance;
}

void RenderObject(Object_t object) {
	ivec2 ProjectedVertices[MAX_OBJECT_VERTICES];
	for (unsigned int i = 0; i < object.num_vertices; i++) {
		ProjectToCanvas(object.vertices[i], ProjectedVertices[i]);
	}
	for (unsigned int i = 0; i < object.num_indices; i++) {
		ivec2 RenderedTriangle[3];
		ivec2_cpy(ProjectedVertices[object.indices[i][0]], RenderedTriangle[0]);
		ivec2_cpy(ProjectedVertices[object.indices[i][1]], RenderedTriangle[1]);
		ivec2_cpy(ProjectedVertices[object.indices[i][2]], RenderedTriangle[2]);
		RenderTriangle(RenderedTriangle, object.colors[i]);
	}
}

void ApplyTransformations(vec3 v, const Transformations_t transformations, vec3 out) {
	mat4 scale, rotate, translate, transform;
	mat4_scale((mat4) MAT4_IDENTITY_INIT, transformations.scale, scale);
	mat4_rotate((mat4) MAT4_IDENTITY_INIT, transformations.rotation, rotate);
	mat4_translate((mat4) MAT4_IDENTITY_INIT, transformations.translation, translate);
	mat4_mul_mat4(rotate, scale, transform);
	mat4_mul_mat4(translate, transform, transform);
	mat4_mul_vec3(transform, v, out);
}

void RenderInstance(Instance_t instance) {
	ivec2 ProjectedVertices[MAX_OBJECT_VERTICES];
	// Applies transformations to vertices and projects them to canvas
	for (unsigned int i = 0; i < instance.object.num_vertices; i++) {
		vec3 v;
		ApplyTransformations(instance.object.vertices[i], instance.transformations, v);
		ProjectToCanvas(v, ProjectedVertices[i]);
	}
	for (unsigned int i = 0; i < instance.object.num_indices; i++) {
		ivec2 RenderedTriangle[3];
		ivec2_cpy(ProjectedVertices[instance.object.indices[i][0]], RenderedTriangle[0]);
		ivec2_cpy(ProjectedVertices[instance.object.indices[i][1]], RenderedTriangle[1]);
		ivec2_cpy(ProjectedVertices[instance.object.indices[i][2]], RenderedTriangle[2]);
		RenderTriangle(RenderedTriangle, instance.object.colors[i]);
	}
}
