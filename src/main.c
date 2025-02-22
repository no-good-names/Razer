#include <fenv.h>
#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#define RENDER_WIREFRAME 1
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

int main(__attribute__((unused)) int argc, __attribute__((unused)) char *argv[]) {
	init_renderer(SCREEN_WIDTH, SCREEN_HEIGHT);

	// Test Objects and Instances
	const Object_t square = create_object(vertices[0], triangles[0], 8, 12, colors);

	Instance_t instances[1] = {0};

	create_instance(&instances[0], square, (Transformations_t) {
		.scale = 1.0f,
		.rotation = {0.00f, 0.00f, 0.00f},
		.translation = {0, 0, 5}
	});


	// Create test scene
	Scene_t scene = create_scene(instances, 1);

    while (running == true) {
    	updateEvents();

        // Inputs
    	const uint8_t *keys = SDL_GetKeyboardState(NULL);
    	if(keys[SDL_SCANCODE_ESCAPE]) {
			running = false;
		}
    	if (keys[SDL_SCANCODE_W]) {
    		vec3 backwards = {0};
    		vec3_normalize( (vec3) {
				sinf(g_camera.view_dir[0]),
				sinf(g_camera.view_dir[1]),
				cosf(g_camera.view_dir[0])
			}, backwards);
    		vec3_scale(backwards, 0.05f, backwards);
    		vec3_add(g_camera.position, backwards, g_camera.position);
    	}
    	if (keys[SDL_SCANCODE_S]) {
    		vec3 backwards = {0};
    		vec3_normalize( (vec3) {
				sinf(g_camera.view_dir[0]),
				sinf(g_camera.view_dir[1]),
				cosf(g_camera.view_dir[0])
			}, backwards);
    		vec3_scale(backwards, 0.05f, backwards);
    		vec3_sub(g_camera.position, backwards, g_camera.position);
    	}
    	if (keys[SDL_SCANCODE_A]) {

    		// Strafe right (perpendicular to the view direction)
    		vec3 left = {0};
    		vec3_normalize( (vec3) {
				sinf(g_camera.view_dir[0] - M_PI_2),
				0.0f,
				cosf(g_camera.view_dir[0] - M_PI_2)
			}, left);
    		vec3_scale(left, 0.05f, left);
    		vec3_add(g_camera.position, left, g_camera.position);
    	}
    	if (keys[SDL_SCANCODE_D]) {
    		// Strafe right (perpendicular to the view direction)
    		vec3 right = {0};
    		vec3_normalize( (vec3) {
				sinf(g_camera.view_dir[0] + M_PI_2),
				0.0f,
				cosf(g_camera.view_dir[0] + M_PI_2)
			}, right);
    		vec3_scale(right, 0.05f, right);
    		vec3_add(g_camera.position, right, g_camera.position);
    	}
    	// TODO: FIX ROTATION
    	// if (keys[SDL_SCANCODE_RIGHT])
    	// 	g_camera.view_dir[2] += DEG2RAD(1.0f);
    	// if (keys[SDL_SCANCODE_LEFT])
    	// 	g_camera.view_dir[2] -= DEG2RAD(1.0f);

    	apply_transformation(&scene.instances[0], (Transformations_t) {
			.scale = 1.0f,
			.rotation = {0.0f, 0.1f * dt.deltaTime, 0.0f},
			.translation = {0, 0, 0}});

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