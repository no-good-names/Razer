#include <fenv.h>
#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#define RENDER_WIREFRAME 0
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

#include "gfx/gfx.h"

struct {
	uint32_t pixels[SCREEN_WIDTH * SCREEN_HEIGHT]; // buffer / canvas
	Camera_t camera;
} state;

v3_t vertices[1][8] = {
	{
		{1, 1, 1},
		{-1, 1, 1},
		{-1, -1, 1},
		{1, -1, 1},
		{1, 1, -1},
		{-1, 1, -1},
		{-1, -1, -1},
		{1, -1, -1}
	}
};

vec3 vertices_m[1][8] = {
	{
		{1, 1, 1},
		{-1, 1, 1},
		{-1, -1, 1},
		{1, -1, 1},
		{1, 1, -1},
		{-1, 1, -1},
		{-1, -1, -1},
		{1, -1, -1}
	}
};

iv3_t triangles[1][12] = {
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

ivec3 triangles_m[1][12] = {
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

v3_t vertices2[1][5] = {
	{
		{-1, -1, 1},
		{-1, -1, -1},
		{1, -1, 1},
		{1, -1, -1},
		{ 0, 1, 0}
	}
};

iv3_t triangles2[1][6] = {
	{
		{0, 1, 4},
		{0, 2, 4},
		{2, 3, 4},
		{2, 3, 4},
		{1, 3, 4},
		{1, 2, 3}
	}
};

uint32_t colors2[6] = {
	RED,
	GREEN,
	BLUE,
	YELLOW,
	PURPLE,
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
	init_renderer(state.pixels, SCREEN_WIDTH, SCREEN_HEIGHT);

	state.camera = create_camera((v3_t) {0, 0, 0}, (v2_t) {0, 0});

	const Object_t cube = create_object_m(vertices_m[0], triangles_m[0], 8, 12, colors);

	Instance_t instances[2] = {0};
	Instance_t instances2[1] = {0};

	create_instance_m(&instances2[0], cube, (Transformations_t) {
		.scale = 1.0f,
		.rotation = (v3_t) {0.00f, 0.00f, 0.00f},
		.translation = (v3_t) {0, 0, 2}
	});

	// Create test scene
	Scene_t scene = create_scene(instances, 2);

    while (running == true) {
    	updateEvents();
    	update_camera(&state.camera);

        // Inputs
    	const uint8_t *keys = SDL_GetKeyboardState(NULL);
    	if (keys[SDL_SCANCODE_W]) {
    		// Move forward in the direction of the view
    		v3_t forward = v3_normalize((v3_t) {
				.x = sinf(state.camera.view_dir.x),
				.y = sinf(state.camera.view_dir.y),
				.z = cosf(state.camera.view_dir.x)
			});
    		state.camera.position = v3_add(state.camera.position, v3_scale(forward, 0.05f));
    	}
    	if (keys[SDL_SCANCODE_S]) {
    		// Move backward opposite to the view direction
    		v3_t backward = v3_normalize((v3_t) {
				.x = sinf(state.camera.view_dir.x),
				.y = sinf(state.camera.view_dir.y),
				.z = cosf(state.camera.view_dir.x)
			});
    		state.camera.position = v3_sub(state.camera.position, v3_scale(backward, 0.05f));
    	}
    	if (keys[SDL_SCANCODE_A]) {
    		// Strafe left (perpendicular to the view direction)
    		v3_t left = v3_normalize((v3_t) {
				.x = sinf(state.camera.view_dir.x - M_PI_2),
				.y = 0.0f,
				.z = cosf(state.camera.view_dir.x - M_PI_2)
			});
    		state.camera.position = v3_add(state.camera.position, v3_scale(left, 0.05f));
    	}
    	if (keys[SDL_SCANCODE_D]) {
    		// Strafe right (perpendicular to the view direction)
    		v3_t right = v3_normalize((v3_t) {
				.x = sinf(state.camera.view_dir.x + M_PI_2),
				.y = 0.0f,
				.z = cosf(state.camera.view_dir.x + M_PI_2)
			});
    		state.camera.position = v3_add(state.camera.position, v3_scale(right, 0.05f));
    	}
    	if (keys[SDL_SCANCODE_RIGHT])
    		state.camera.view_dir.x += 0.01f;
    	if (keys[SDL_SCANCODE_LEFT])
    		state.camera.view_dir.x -= 0.01f;


    	// Rendering
    	memset(state.pixels, 0, sizeof(state.pixels)); // clear buffer
    	// RenderScene(scene);
		renderObject_m(cube);

		// Update screen
        updateWindow();
    }
    destroyWindow();
    return 0;
}