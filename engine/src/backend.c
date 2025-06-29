#include <Razer/backend.h>
#include <stdint.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

uint32_t *pixels = NULL;
float *zbuffer = NULL;
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Texture *texture = NULL;
bool quit = false;
int screen_size[2] = {0, 0};
int window_size[2] = {0, 0};
float aspect_ratio[2] = {0.0f, 0.0f};

void init_video(const uint16_t w, const uint16_t h, const uint16_t window_scale) {
    fprintf(stderr, "Initializing video with %d x %d\n", w, h);
    screen_size[0] = w;
    screen_size[1] = h;
    window_size[0] = w * window_scale;
    window_size[1] = h * window_scale;
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		printf("SDL_Init Error: %s\n", SDL_GetError());
		exit(1);

	}
    window = SDL_CreateWindow("Demo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w * window_scale,
        h * window_scale, 0);
    if (window == NULL) {
		printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
		exit(1);
	}
    renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) {
		printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
		exit(1);
	}
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING,
        screen_size[0], screen_size[1]);
    if (texture == NULL) {
		printf("SDL_CreateTexture Error: %s\n", SDL_GetError());
		exit(1);
	}
    fprintf(stderr, "Video initialized successfully\n");
    fprintf(stderr, "Window size: %d x %d\n", window_size[0], window_size[1]);
    fprintf(stderr, "Screen size: %d x %d\n", screen_size[0], screen_size[1]);
    quit = false;
    pixels = (uint32_t *) malloc(w * h * sizeof(uint32_t));
    if (pixels == NULL) {
        printf("Failed to allocate memory for pixels\n");
        exit(1);
    }
    zbuffer = (float *) malloc(w * h * sizeof(int));
    if (zbuffer == NULL) {
        printf("Failed to allocate memory for zbuffer\n");
        exit(1);
    }
    memset(pixels, 0, get_screen_width() * get_screen_height() * sizeof(uint32_t));
    for (int i = screen_size[0] * screen_size[1]; i--;) {
        zbuffer[i] = -FLT_MAX;
    }
}

void update_events() {
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        switch(event.type) {
            case SDL_QUIT:
                quit = true;
                break;
            default: break;
        }
    }
}

void update_video() {
    SDL_UpdateTexture(texture, NULL, pixels, get_screen_width() * sizeof(uint32_t));
    SDL_RenderCopyEx(renderer, texture, NULL, NULL, 0.0f, NULL, SDL_FLIP_VERTICAL);
    SDL_RenderPresent(renderer);
}

void destroy_video() {
    fprintf(stderr, "Destroying video\n");
    if (pixels) {
        free(pixels);
    }
    if (zbuffer) {
        free(zbuffer);
    }
    if (texture) {
        SDL_DestroyTexture(texture);
    }
    if (renderer) {
        SDL_DestroyRenderer(renderer);
    }
    if (window) {
        SDL_DestroyWindow(window);
    }
    fprintf(stderr, "Video destroyed successfully\n");
    fprintf(stderr, "Exiting...\n");
    SDL_Quit();
    exit(0);
}