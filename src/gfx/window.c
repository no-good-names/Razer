//
// Created by cp176 on 3/15/2025.
//

//
// Created by cp176 on 2/9/2025.
//

#include "window.h"

#include "typedef.h"
#include <math.h>

uint32_t *pixels = NULL;
float aspect_ratio[2] = {0, 0};
int screen_size[2] = {0, 0};
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Texture *texture = NULL;
bool running = false;
uint8_t TRIANGLE_TYPE = 0;
struct dt dt = {0, 0, 0};

void init_renderer(const int width, const int height) {
	pixels = (uint32_t *) malloc(height * width * sizeof(uint32_t));;
	screen_size[0] = width;
	screen_size[1] = height;
	aspect_ratio[0]= (float) width / height;
	aspect_ratio[1] = aspect_ratio[0] * (float) height / width;
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		printf("SDL_Init Error: %s\n", SDL_GetError());
		exit(1);
	}
	window = SDL_CreateWindow("Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screen_size[0], screen_size[1], 0);
	if (window == NULL) {
		printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
		exit(1);
	}
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == NULL) {
		printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
		exit(1);
	}
	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, screen_size[0], screen_size[1]);
	if (texture == NULL) {
		printf("SDL_CreateTexture Error: %s\n", SDL_GetError());
		exit(1);
	}
	running = true;

	// g_camera = create_camera((vec3) {0, 0, 0}, (vec3) {0, 0, 1});
	float lastTime = (float) SDL_GetTicks();
}

void update_events() {
	// Calculate delta time every frame
	dt.current = (float) SDL_GetTicks();
	dt.deltaTime = dt.current - dt.last;
	dt.last = dt.current;
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			running = false;
		}
	}
}

void update_renderer() {
	SDL_UpdateTexture(texture, NULL, pixels, screen_size[0] * sizeof(uint32_t));
    SDL_RenderCopyEx(renderer, texture, NULL, NULL, 0, NULL, SDL_FLIP_NONE);
	SDL_RenderPresent(renderer);
}

void destroy_renderer() {
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
