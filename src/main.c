#include <fenv.h>
#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#include "gfx/camera.h"
#include "gfx/gfx.h"

#define RENDER_WIREFRAME 1

struct {
	SDL_Window *window; // canvas
	SDL_Renderer *renderer;
	SDL_Texture *texture;
	uint32_t pixels[SCREEN_WIDTH * SCREEN_HEIGHT]; // viewport
	bool running;
	Camera_t camera;
} state;

v2_t ViewportToCanvas(const v2_t v) {
    v2_t canvas = {
        .x = v.x * SCREEN_WIDTH / VIEWPORT_WIDTH,
        .y = v.y * SCREEN_HEIGHT / VIEWPORT_HEIGHT
    };
    return canvas;
}

v2_t ProjectVertex(const v3_t v) {
	if (v.z == 0.0f) {
		fprintf(stderr, "Error: Division by zero.\n");
		return (v2_t){0.0f, 0.0f};
	}
	const float d = 1.0f; // depth
	v2_t dv = {
		(v.x * d) / v.z,
		(v.y * d) / v.z
	};

	dv = ViewportToCanvas(dv);
	return dv;
}

void setPixel(int32_t x, int32_t y, const uint32_t color) {
	// start at the middle of the screen
	x += SCREEN_WIDTH/2;
	y += SCREEN_HEIGHT/2;
	// Check if x or y is out of bounds
	// EX: x=-SCREEN_WIDTH/2 - 1; x+= SCREEN_WIDTH/2; x=-1; doesn't draw
	if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT) {
		return;
	}
	state.pixels[(y * SCREEN_WIDTH) + x] = color;
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

v3_t vertices2[1][5] = {
	{
		{-1, -1, 1},
		{-1, -1, -1},
		{1, -1, 1},
		{1, -1, -1},
		{ 0, 1, 0}
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

iv3_t triangles2[1][6] = {
	{
		{0, 1, 4},
		{0, 2, 4},
		{2, 3, 4},
		{4, 3, 4},
		{1, 3, 4},
		{1, 2, 3}
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

uint32_t colors2[6] = {
	RED,
	GREEN,
	BLUE,
	YELLOW,
	PURPLE,
	CYAN
};

void renderTriangle(v2_t projected[3], uint32_t color) {
#if RENDER_WIREFRAME == 1
	WireFrameTriangle(setPixel, projected[0], projected[1], projected[2], color);
#else
	FilledTriangle(setPixel, projected[0], projected[1], projected[2], color);
#endif
}

v3_t rotateX(v3_t v, float angle) {
	float cosAngle = cosf(angle);
	float sinAngle = sinf(angle);
	return (v3_t) {
		.x = v.x * cosAngle - v.z * sinAngle,
		.y = v.y,
		.z = v.x * sinAngle + v.z * cosAngle
	};
}

void renderObject(Object_t object) {
	static v2_t projectedVertices[MAX_OBJECT_VERTICES];
	for (int i = 0; i < object.numVertices; i++) {
		projectedVertices[i] = ProjectVertex(v3_add(object.vertices[i], v3_sub(object.center, state.camera.position)));
	}
	for (int i = 0; i < object.numTriangles; i++) {
		v2_t renderedTriangle[3] = {
			projectedVertices[object.triangles[i].x],
			projectedVertices[object.triangles[i].y],
			projectedVertices[object.triangles[i].z],
		};
		renderTriangle(renderedTriangle, object.color[i]);
	}
}

void RenderScene(const Scene_t scene) {
	for (int i = 0; i < scene.numObjects; i++) {
		renderObject(scene.objects[i]);
	}
}

void ClearScreen(uint32_t color) {
	for (int y = -SCREEN_HEIGHT/2; y < SCREEN_HEIGHT / 2; y++) {
		for (int x = -SCREEN_WIDTH/2; x < SCREEN_WIDTH/2; x++) {
			setPixel(x, y, color);
		}
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
	SDL_Init(SDL_INIT_VIDEO);
    state.window = SDL_CreateWindow("Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    state.renderer = SDL_CreateRenderer(state.window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    state.texture = SDL_CreateTexture(state.renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT);
    state.running = true;

	state.camera = create_camera((v3_t) {0, 0, 0}, (v3_t) {1, 0, 0});

	// Test Scene
	Object_t objects[1] = {
		create_object((v3_t) {0, 0, 8}, vertices[0], triangles[0], 8, 12, colors)
	};

	Object_t objects2[1] = {
		create_object((v3_t) {0, 0, 8}, vertices2[0], triangles2[0], 5, 6, colors2)
	};

	Scene_t scene = create_scene(objects, 1);
	Scene_t scene2 = create_scene(objects2, 1);
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
    	if (keys[SDL_SCANCODE_W] && keywait(10)) {
    		if (state.camera.position.z < 6) {
				state.camera.position.z += 0.1f;
			}
    		else {
    			fprintf(stderr, "Program will crash beyond this point, I need to fix it.\n");
    		}
    	}
    	if (keys[SDL_SCANCODE_S] && keywait(10)) {
    		state.camera.position.z -= 0.1f;
    	}
        if (keys[SDL_SCANCODE_D] && keywait(10)) {
        	state.camera.position.x += 0.1f;
        }
    	if (keys[SDL_SCANCODE_A] && keywait(10)) {
    		state.camera.position.x -= 0.1f;
    	}
    	if (keys[SDL_SCANCODE_1] && keywait(10)) {
    		i = 0;
		}
    	if (keys[SDL_SCANCODE_2] && keywait(10)) {
    		i = 1;
    	}

    	// Rendering
    	memset(state.pixels, 0, sizeof(state.pixels)); // clear buffer
        ClearScreen(0);
    	if (i == 0) {
			RenderScene(scene);
		}
		if (i == 1) {
			RenderScene(scene2);
		}

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