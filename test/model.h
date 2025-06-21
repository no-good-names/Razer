//
// Created by cp176 on 6/20/2025.
//

#ifndef MODEL_H
#define MODEL_H

#include <cglm/cglm.h>

typedef struct {
	vec3 *vertices;
	ivec3 *faces;
	int nVertices;
	int nFaces;
} Model_t;

// TODO: Read obj files and copy into Model struct type
void read_obj_file(Model_t *model, char *filename);

#endif //MODEL_H
