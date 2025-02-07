#include <fenv.h>
#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#include "gfx/gfx.h"

#define RENDER_WIREFRAME 1

struct {
	SDL_Window *window; // canvas
	SDL_Renderer *renderer;
	SDL_Texture *texture;
	uint32_t pixels[SCREEN_WIDTH * SCREEN_HEIGHT]; // buffer / canvas
	bool running;
	Camera_t camera;
} state;

void ProjectToCanvas(iv2_t *dest, const v3_t v) {
	if (v.z <= 0.0f) {
		return;
	}
	const float d = 1.0f; // depth
	// Perspective projection
	v2_t dv = {
		(v.x * d) / v.z,
		(v.y * d) / v.z
	};

	// NOTE: THIS IS VIEWPORT TO CANVAS
	*dest = (iv2_t) {
		.x = dv.x * (SCREEN_WIDTH / VIEWPORT_WIDTH),
		.y = dv.y * (SCREEN_HEIGHT / VIEWPORT_HEIGHT)
	};
}

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

void renderTriangle(iv2_t projected[3], uint32_t color) {
#if RENDER_WIREFRAME == 1
	WireFrameTriangle(projected[0], projected[1], projected[2], color);
#else
	FillTriangle(projected[0], projected[1], projected[2], color);
#endif
}

v3_t rotate_scene(v3_t v, v2_t rotation) {
	v = rotateX(v, rotation.x);
	v = rotateY(v, rotation.y);
	v = rotateZ(v, 0);
	return v;
}

void renderObject(const Object_t object) {
	iv2_t projectedVertices[MAX_OBJECT_VERTICES];
	for (int i = 0; i < object.numVertices; i++) {
		ProjectToCanvas(&projectedVertices[i], rotate_scene(v3_add(object.vertices[i],
			v3_sub(object.center, state.camera.position)), state.camera.view_dir));
	}
	for (int i = 0; i < object.numTriangles; i++) {
		iv2_t renderedTriangle[3] = {
			projectedVertices[object.triangles[i].x],
			projectedVertices[object.triangles[i].y],
			projectedVertices[object.triangles[i].z],
		};
		renderTriangle(renderedTriangle, object.color[i]);
	}
}

void RenderScene(const Scene_t scene) {
	for (int i = 0; i < scene.numInstances; i++) {
		renderObject(scene.instances[i].object);
	}
}

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
	initPixels(state.pixels);
	SDL_Init(SDL_INIT_VIDEO);
    state.window = SDL_CreateWindow("Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    state.renderer = SDL_CreateRenderer(state.window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    state.texture = SDL_CreateTexture(state.renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT);
    state.running = true;

	state.camera = create_camera((v3_t) {0, 0, 0}, (v2_t) {0, 0});

	// Test Objects and Instances
	const Object_t square = create_object(vertices[0], triangles[0], 8, 12, colors);
	const Object_t pyramid = create_object(vertices2[0], triangles2[0], 5, 6, colors2);

	Instance_t instances[2] = {0};

	create_instance(&instances[0], square, (Transformations_t) {
		.scale = 1.0f,
		.rotation = (v3_t) {0.00f, 0.00f, 0.00f},
		.translation = (v3_t) {2, 0, 8}
	});

	create_instance(&instances[1], pyramid, (Transformations_t) {
		.scale = 1.0f,
		.rotation = (v3_t) {0.00f, 0.00f, 0.00f},
		.translation = (v3_t) {-2, 0, 8}
	});

	// Create test scene
	Scene_t scene = create_scene(instances, 2);
	int i = 0;
    while (state.running) {
    	// SDL2 events
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                state.running = false;
                goto end;
            }
        }

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

    	apply_transformation(&scene.instances[0], (Transformations_t) {
			.scale = 1.0f,
			.rotation = (v3_t) {0.00f, 0.01f, 0.00f},
			.translation = (v3_t) {0, 0, 0}});
    	apply_transformation(&scene.instances[1], (Transformations_t) {
			.scale = 1.0f,
			.rotation = (v3_t) {0.01f, 0.00f, 0.00f},
			.translation = (v3_t) {0, 0, 0}});

    	// Rendering
    	memset(state.pixels, 0, sizeof(state.pixels)); // clear buffer
    	for (int y = -SCREEN_HEIGHT/2; y < SCREEN_HEIGHT / 2; y++) {
    		for (int x = -SCREEN_WIDTH/2; x < SCREEN_WIDTH/2; x++) {
    			setPixel(x, y, BLACK);
    		}
    	}
    	RenderScene(scene);

		// Update screen
        SDL_UpdateTexture(state.texture, NULL, state.pixels, SCREEN_WIDTH * sizeof(state.pixels[0]));
        SDL_RenderCopyEx(
            state.renderer,
            state.texture,
            NULL,
            NULL,
            0.0,
            NULL,
            SDL_FLIP_VERTICAL);
        SDL_RenderPresent(state.renderer);
    }
    end:
    SDL_DestroyTexture(state.texture);
    SDL_DestroyRenderer(state.renderer);
    SDL_DestroyWindow(state.window);
    SDL_Quit();
    return 0;
}