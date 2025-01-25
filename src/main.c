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
	uint32_t pixels[SCREEN_WIDTH * SCREEN_HEIGHT]; // viewport
	bool running;
	struct deltaTime {
		uint32_t lastTime;
		uint32_t currentTime;
		float deltaTime;
	} dt;
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
		printf("Error: Division by zero.\n");
		return (v2_t){0.0f, 0.0f};
	}
	float d = 1;
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

v3_t vertices[8] = {
	{-2, -0.5f, 5.0f},
	{-2, 0.5f, 5.0f},
	{-1, 0.5f, 5.0f},
	{-1, -0.5f, 5.0f},
	{-2, -0.5f, 6.0f},
	{-2, 0.5f, 6.0f},
	{-1, 0.5f, 6.0f},
	{-1, -0.5f, 6.0f}
};

v3_t vertices2[8] = {
	{2, -0.5f, 5.0f},
	{2, 0.5f, 5.0f},
	{1, 0.5f, 5.0f},
	{1, -0.5f, 5.0f},
	{2, -0.5f, 6.0f},
	{2, 0.5f, 6.0f},
	{1, 0.5f, 6.0f},
	{1, -0.5f, 6.0f}
};

iv3_t triangles[12] = {
	{0, 1, 2},
	{0, 2, 3},
	{4, 5, 6},
	{4, 6, 7},
	{0, 1, 5},
	{0, 5, 4},
	{1, 2, 6},
	{1, 6, 5},
	{2, 3, 7},
	{2, 7, 6},
	{3, 0, 4},
	{3, 4, 7}
};

iv3_t triangles2[12] = {
	{0, 1, 2},
	{0, 2, 3},
	{4, 5, 6},
	{4, 6, 7},
	{0, 1, 5},
	{0, 5, 4},
	{1, 2, 6},
	{1, 6, 5},
	{2, 3, 7},
	{2, 7, 6},
	{3, 0, 4},
	{3, 4, 7}
};

uint32_t colors[12] = {
	0xFFFF0000,
	0xFF00FF00,
	0xFF0000FF,
	0xFFFFFF00,
	0xFFFF00FF,
	0xFF00FFFF,
	0xFF000000,
	0xFFFFFFFF,
	0xFF00FF00,
	0xFF00FF00,
	0xFF00FF00,
	0xFF00FF00
};

uint32_t colors2[12] = {
	0xFFFF0000,
	0xFF00FF00,
	0xFF0000FF,
	0xFFFFFF00,
	0xFFFF00FF,
	0xFF00FFFF,
	0xFF000000,
	0xFFFFFFFF,
	0xFF00FF00,
	0xFF00FF00,
	0xFF00FF00,
	0xFF00FF00
};

void renderTriangle(v2_t projected[3], uint32_t color) {
#if RENDER_WIREFRAME == 1
	WireFrameTriangle(setPixel, projected[0], projected[1], projected[2], color);
#else
	FilledTriangle(setPixel, projected[0], projected[1], projected[2], color);
#endif
}

void renderObject(const v3_t *vertices, const iv3_t *triangles, const int numVertices, const int numTriangles, const uint32_t color) {
	v2_t *projectedVertices = malloc(numVertices * sizeof(v3_t));
	for (int i = 0; i < numVertices; i++) {
		projectedVertices[i] = ProjectVertex(vertices[i]);
	}
	for (int i = 0; i < numTriangles; i++) {
		iv3_t triangle = triangles[i];
		v2_t *renderedTriangle = malloc(3 * sizeof(v2_t));
		renderedTriangle[0] = projectedVertices[triangle.x];
		renderedTriangle[1] = projectedVertices[triangle.y];
		renderedTriangle[2] = projectedVertices[triangle.z];
		renderTriangle(renderedTriangle, color);
		free(renderedTriangle);
	}
	free(projectedVertices);
}

void RenderScene(const Scene_t scene) {
	for (int i = 0; i < scene.numObjects; i++) {
		renderObject(scene.objects[i].vertices,
			scene.objects[i].triangles,
			scene.objects[i].numVertices,
			scene.objects[i].numTriangles,
			*scene.objects[i].color);
	}
}

void ClearScreen(uint32_t color) {
	memset(state.pixels, 0, sizeof(state.pixels));
	for (int y = -SCREEN_HEIGHT/2; y < SCREEN_HEIGHT / 2; y++) {
		for (int x = -SCREEN_WIDTH/2; x < SCREEN_WIDTH/2; x++) {
			setPixel(x, y, color);
		}
	}
}

int main(__attribute__((unused)) int argc, __attribute__((unused)) char *argv[]) {
	SDL_Init(SDL_INIT_VIDEO);
    state.window = SDL_CreateWindow("Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    state.renderer = SDL_CreateRenderer(state.window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    state.texture = SDL_CreateTexture(state.renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT);
    state.running = true;
    state.dt.lastTime = SDL_GetTicks();
    state.dt.currentTime = 0;
    state.dt.deltaTime = 0;
	Object_t cube = create_object(vertices, triangles, 8, 12, colors);
	Object_t cube2 = create_object(vertices2, triangles2, 8, 12, colors);
	Object_t *objects = malloc(2 * sizeof(Object_t));
	objects[0] = cube;
	objects[1] = cube2;
	Scene_t scene = create_scene(objects, 2);
    while (state.running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                state.running = false;
                goto end;
            }
        }

        // Movement
        const uint8_t *keys = SDL_GetKeyboardState(NULL);
        if (keys[SDL_SCANCODE_W]) {
        	printf("Test");
        }

        ClearScreen(0xFFFFFFFF);
    	RenderScene(scene);

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