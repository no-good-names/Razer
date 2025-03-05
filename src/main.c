#include <fenv.h>
#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#define SHOW_FPS 1
#include "gfx/gfx.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

vec3 vertices[1][8] = {
	{
		{1, 1, 1}, // 0
		{-1, 1, 1}, // 1
		{-1, -1, 1}, // 2
		{1, -1, 1}, // 3
		{1, 1, -1}, // 4
		{-1, 1, -1}, // 5
		{-1, -1, -1}, // 6
		{1, -1, -1} // 7
	}
};

ivec3 triangles[1][12] = {
	{
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
	}
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

// 2d square
vec3 vertices_arr[4] = {
	{1, 1, 0},
	{-1, 1, 0},
	{-1, -1, 0},
	{1, -1, 0}
};

ivec3 triangles_arr[2] = {
	{0, 1, 2},
	{0, 2, 3}
};

uint32_t faceColors[2] = {
	RED,
	BLUE
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

// distance test
float distance(vec3 a, vec3 b) {
	return sqrtf(powf(b[0] - a[0], 2) + powf(b[1] - a[1], 2) + powf(b[2] - a[2], 2));
}

void debugPrint(const char* msg, vec3 v) {
	printf("%s: (%f, %f, %f) | Length: %f\n", msg, v[0], v[1], v[2], vec3_length(v));
}

int main(__attribute__((unused)) int argc, __attribute__((unused)) char *argv[]) {
	init_renderer(SCREEN_WIDTH, SCREEN_HEIGHT);

	// Test Objects and Instances
	const Object_t cube = create_object(vertices[0], triangles[0], 8, 12, colors);
	const Object_t square = create_object(vertices_arr, triangles_arr, 4, 2, faceColors);
	Instance_t instances[2] = {0};

	create_instance(&instances[0], square, (Transformations_t) {
		.scale = 1.0f,
		.rotation = {0.00f, 0.00f, 0.00f},
		.translation = {-1.5f, 0, 5}
	});
	create_instance(&instances[1], cube, (Transformations_t) {
		.scale = 1.0f,
		.rotation = {0.00f, 0.00f, 0.00f},
		.translation = {1.5f, 0, 5}
	});

	// Create test scene
	Scene_t scene = create_scene(instances, 2);

	// New: Set Draw Mode LINE or FILLED mode
	SetDrawMode(LINE);
    while (running == true) {
    	updateEvents();

        // Inputs
    	const uint8_t *keys = SDL_GetKeyboardState(NULL);
    	if(keys[SDL_SCANCODE_ESCAPE]) {
			running = false;
		}

   //  	apply_transformation(&scene.instances[0], (Transformations_t) {
			// .scale = 1.0f,
			// .rotation = {0.0f, 1.0f, 0.0f},
			// .translation = {0, 0, 0}});
   //  	apply_transformation(&scene.instances[1], (Transformations_t) {
			// .scale = 1.0f,
			// .rotation = {0.0f, 1.0f, 0.0f},
			// .translation = {0, 0, 0}});
    	printf("%f\n", distance(scene.instances[1].object.vertices[0], scene.instances[1].object.vertices[1]));

    	// Rendering
    	memset(pixels, 0, PIXELS_SIZE); // clear buffer
    	RenderScene(scene);

		// Update screen
        updateWindow();

#if SHOW_FPS == 1
    	char title[256];
    	sprintf(title, "TEST - FPS: %f", 1000.0f / dt.deltaTime);
    	SDL_SetWindowTitle(window, title);
#elif SHOW_FPS == 2
    	char title[256];
    	sprintf(title, "FPS: %f", 1000.0f / dt.deltaTime);
    	fprintf(stderr, "%s\n", title);
#endif
    }
    destroyWindow();
    return 0;
}