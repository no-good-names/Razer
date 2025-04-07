//
// Created by cp176 on 3/15/2025.
//

#include <SDL2/SDL.h>
#include <stdio.h>

#include "gfx/gfx.h"

vec3 vertices[8] = {
	{1, 1, 1}, // 0
	{-1, 1, 1}, // 1
	{-1, -1, 1}, // 2
	{1, -1, 1}, // 3
	{1, 1, -1}, // 4
	{-1, 1, -1}, // 5
	{-1, -1, -1}, // 6
	{1, -1, -1} // 7
};

ivec3 indices[12] = {
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

int main(int argc, char *argv[]) {
	init_renderer(800, 600);
	set_window_title("Rasterizer Demo");

	const Object_t object = CreateObject(vertices, indices, colors, 8, 12);

	Instance_t instance = CreateInstance(object, (vec3) {-1.5f, 0.0f, 6.0f}, (vec3) {0.0f, 0.0f, 0.0f}, (vec3) {1.0f, 1.0f, 1.0f});
	Instance_t instance1 = CreateInstance(object, (vec3) {1.5f, 0.0f, 6.0f}, (vec3) {0.0f, 0.0f, 0.0f}, (vec3) {1.0f, 1.0f, 1.0f});

	SetDrawType(TRIANGLE_WIREFRAME);
	show_fps(false);
	while (running) {
		update_events();
		memset(pixels, 0, PIXELS_SIZE);

		RenderInstance(instance);
		RenderInstance(instance1);

		const uint8_t *keys = SDL_GetKeyboardState(NULL);
		if (keys[SDL_SCANCODE_ESCAPE]) running = false;
		if (keys[SDL_SCANCODE_1]) SetDrawType(TRIANGLE_WIREFRAME);
		if (keys[SDL_SCANCODE_2]) SetDrawType(TRIANGLE_FILLED);
		instance.transformations.rotation[0] += 1.0f;
		instance1.transformations.rotation[1] += 1.0f;

		update_renderer();
	}
	destroy_renderer();
	return 0;
}
