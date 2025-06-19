#include "backend.h"
#include <stdint.h>
#include <SDL3/SDL.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

uint32_t *pixels = NULL;
float *depth_buffer = NULL;
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Texture *texture = NULL;
bool quit = false;
int screen_size[2] = {0, 0};
int window_size[2] = {0, 0};
float aspect_ratio[2] = {0.0f, 0.0f};

void init_video(uint16_t w, uint16_t h, uint16_t window_scale) {
    fprintf(stderr, "Initializing video with %d x %d\n", w, h);
    screen_size[0] = w;
    screen_size[1] = h;
    window_size[0] = w * window_scale;
    window_size[1] = h * window_scale;
    pixels = (uint32_t *) malloc(w * h * sizeof(uint32_t));
    if (pixels == NULL) {
        printf("Failed to allocate memory for pixels\n");
        exit(1);
    }
    depth_buffer = (float *) malloc(w * h * sizeof(float));
    if (depth_buffer == NULL) {
        printf("Failed to allocate memory for depth buffer\n");
        exit(1);
    }
    memset(pixels, 0, get_screen_width() * get_screen_height() * sizeof(uint32_t));
    memset(depth_buffer, 0, get_screen_width() * get_screen_height() * sizeof(float));
    for (int i = 0; i < get_screen_width() * get_screen_height(); i++) {
        depth_buffer[i] = 1.0f;
    }
    if (!SDL_Init(SDL_INIT_VIDEO)) {
		printf("SDL_Init Error: %s\n", SDL_GetError());
		exit(1);

	}
    window = SDL_CreateWindow("Demo", (uint32_t) w * window_scale, (uint32_t) h * window_scale, 0);
    SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
    if (window == NULL) {
		printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
		exit(1);
	}
    renderer = SDL_CreateRenderer(window, NULL);
    if (renderer == NULL) {
		printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
		exit(1);
	}
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, screen_size[0], screen_size[1]);
    if (texture == NULL) {
		printf("SDL_CreateTexture Error: %s\n", SDL_GetError());
		exit(1);
	}
    SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST);
    bool quit = false;
    fprintf(stderr, "Video initialized successfully\n");
    fprintf(stderr, "Window size: %d x %d\n", window_size[0], window_size[1]);
    fprintf(stderr, "Screen size: %d x %d\n", screen_size[0], screen_size[1]);
}

void update_events() {
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        switch(event.type) {
            case SDL_EVENT_QUIT:
                quit = true;
                break;
        }
    }
}

void update_video() {
    SDL_UpdateTexture(texture, NULL, pixels, get_screen_width() * sizeof(uint32_t));
    SDL_RenderTexture(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
}

void destroy_video() {
    fprintf(stderr, "Destroying video\n");
    if (pixels) {
        free(pixels);
        pixels = NULL;
    }
    if (texture) {
        SDL_DestroyTexture(texture);
        texture = NULL;
    }
    if (renderer) {
        SDL_DestroyRenderer(renderer);
        renderer = NULL;
    }
    if (window) {
        SDL_DestroyWindow(window);
        window = NULL;
    }
    fprintf(stderr, "Video destroyed successfully\n");
    fprintf(stderr, "Exiting...\n");
    SDL_Quit();
    exit(0);
}