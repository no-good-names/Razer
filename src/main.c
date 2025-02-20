#include "gfx/math/vec3.h"
#include "gfx/objects.h"
#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#define RENDER_WIREFRAME 1

#include "gfx/gfx.h"

vec3 vertices[8] = {
	{1, 1, 1},
	{-1, 1, 1},
	{-1, -1, 1},
	{1, -1, 1},
	{1, 1, -1},
	{-1, 1, -1},
	{-1, -1, -1},
	{1, -1, -1}
};

ivec3 triangles[12] = {
	{0, 1, 2},
	{0, 2, 3},
	{4, 0, 3},
	{4, 3, 7},
	{5, 4, 7},
	{5, 7, 6},
	{1, 5, 6},
	{1, 6, 2},
	{4, 5, 1},
	{4, 1, 0},
	{2, 6, 7},
	{2, 7, 3}
};

uint32_t colors[12] = {
	RED,
	RED,
	GREEN,
	GREEN,
	BLUE,
	BLUE,
	YELLOW,
	YELLOW,
	PURPLE,
	PURPLE,
	CYAN,
	CYAN
};

bool keywait(int miliseconds) {
	static int lastTime = 0;
	int currentTime = SDL_GetTicks();
	if(currentTime - lastTime > miliseconds) {
		lastTime = currentTime;
		return true;
	}
	return false;
}

int main(__attribute__((unused)) int argc, __attribute__((unused)) char *argv[]) {
	init_renderer(800, 600);

	const Object_t cube = create_object(vertices, triangles, 8, 12, colors);

	Instance_t instances[1];

	create_instance(&instances[0], cube,  (Transformations_t) {
		.scale = 1.0f,
		.rotation = {0, 0, 0},
		.translation = {0, 0, 5}
	});

	Scene_t scene = create_scene(instances, 1);

	while (running == true) {
        updateEvents();
    	memset(pixels, 0, PIXELS_SIZE);
        RenderScene(scene);
		updateWindow();
	}
	destroyWindow();
	return 0;
}
