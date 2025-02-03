//
// Created by cp176 on 1/30/2025.
//

#include "scene.h"

Instance_t clipInstanceAgainstPlane(Instance_t instance, v3_t plane_p, v3_t plane_n) {
	Instance_t clipped_instance = instance;
	Object_t object = instance.object;
	Object_t clipped_object = create_object(object.vertices, object.triangles, object.numVertices, object.numTriangles, object.color);
	int numVertices = 0;
	v3_t previous_vertex = object.vertices[object.numVertices - 1];
	float previous_distance = v3_dot(v3_sub(previous_vertex, plane_p), plane_n);
	for (int i = 0; i < object.numVertices; i++) {
		v3_t vertex = object.vertices[i];
		float distance = v3_dot(v3_sub(vertex, plane_p), plane_n);
		if (distance * previous_distance < 0) {
			v3_t intersection = v3_add(vertex, v3_scale(v3_sub(previous_vertex, vertex), previous_distance / (previous_distance - distance)));
			clipped_object.vertices[numVertices++] = intersection;
		}
		if (distance >= 0) {
			clipped_object.vertices[numVertices++] = vertex;
		}
		previous_vertex = vertex;
		previous_distance = distance;
	}
	clipped_object.numVertices = numVertices;
	clipped_instance.object = clipped_object;
	return clipped_instance;
}

Instance_t clipped_instance(Instance_t *instance, Camera_t camera) {
	Instance_t clipped_object = *instance;
	v3_t camera_position = camera.position;
	v2_t view_dir = camera.view_dir;
	v3_t view_dir_3d = (v3_t) {
		.x = sinf(view_dir.x),
		.y = sinf(view_dir.y),
		.z = cosf(view_dir.x)
	};
	v3_t plane_p = camera_position;
	v3_t plane_n = v3_normalize(view_dir_3d);
	clipped_object = clipInstanceAgainstPlane(clipped_object, plane_p, plane_n);
	plane_p = v3_add(camera_position, v3_scale(view_dir_3d, 0.1f));
	plane_n = v3_negate(plane_n);
	clipped_object = clipInstanceAgainstPlane(clipped_object, plane_p, plane_n);
	return clipped_object;
}

Scene_t clipped_scene(Scene_t scene, Camera_t camera) {
	Scene_t clipped_scene = create_scene(scene.instances, scene.numInstances);
	for (int i = 0; i < scene.numInstances; i++) {
		Instance_t instance = scene.instances[i];
		Instance_t object = instance;
		Instance_t c_instance = clipped_instance(&instance, camera);
		create_instance(&clipped_scene.instances[i], c_instance.object, instance.transformations);
	}
	return clipped_scene;
}