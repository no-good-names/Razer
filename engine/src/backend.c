#include <Razer/backend.h>
#include <stdint.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct global_backend g_backend;

struct global_backend *get_backend_state() {
    return &g_backend;
}

void init_video(uint16_t window_width, uint16_t window_height,
	uint16_t screen_width, uint16_t screen_height) {
    fprintf(stderr, "Initializing video with d%d x %d\n", screen_width, screen_height);
    g_backend.screen_size[0] = screen_width;
    g_backend.screen_size[1] = screen_height;
    g_backend.window_size[0] = window_width;
    g_backend.window_size[1] = window_height;
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		printf("SDL_Init Error: %s\n", SDL_GetError());
		exit(1);

	}
    g_backend.window = SDL_CreateWindow("Demo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_width,
        window_height, 0);
    if (g_backend.window == NULL) {
		printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
		exit(1);
	}
    g_backend.renderer = SDL_CreateRenderer(g_backend.window, 0, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (g_backend.renderer == NULL) {
		printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
		exit(1);
	}
    g_backend.texture = SDL_CreateTexture(g_backend.renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING,
        g_backend.screen_size[0], g_backend.screen_size[1]);
    if (g_backend.texture == NULL) {
		printf("SDL_CreateTexture Error: %s\n", SDL_GetError());
		exit(1);
	}
    fprintf(stderr, "Video initialized successfully\n");
    fprintf(stderr, "Window size: %d x %d\n", g_backend.window_size[0], g_backend.window_size[1]);
    fprintf(stderr, "Screen size: %d x %d\n", g_backend.screen_size[0], g_backend.screen_size[1]);
    g_backend.quit = false;
    g_backend.pixels = (uint32_t *) malloc(screen_width * screen_height * sizeof(uint32_t));
    if (g_backend.pixels == NULL) {
        printf("Failed to allocate memory for pixels\n");
        exit(1);
    }
    g_backend.zbuffer = (float *) malloc(screen_width * screen_height * sizeof(float));
    if (g_backend.zbuffer == NULL) {
        printf("Failed to allocate memory for zbuffer\n");
        exit(1);
    }
    memset(g_backend.pixels, 0, get_screen_width() * get_screen_height() * sizeof(uint32_t));
    for (int i = g_backend.screen_size[0] * g_backend.screen_size[1]; i--;) {
        g_backend.zbuffer[i] = FLT_MAX;
    }
}

void key_scancode() {
    const uint8_t *key = SDL_GetKeyboardState(NULL);
    if (key[SDL_SCANCODE_ESCAPE]) {}
}

void update_events() {
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        switch(event.type) {
            case SDL_QUIT:
                g_backend.quit = true;
                break;
            default: break;
        }
    }
}

void update_video() {
    SDL_UpdateTexture(g_backend.texture, NULL, g_backend.pixels, get_screen_width() * sizeof(uint32_t));
    SDL_RenderCopyEx(g_backend.renderer, g_backend.texture, NULL, NULL, 0.0f, NULL, SDL_FLIP_VERTICAL);
    SDL_RenderPresent(g_backend.renderer);
}

void destroy_video() {
    fprintf(stderr, "Destroying video\n");
    free(g_backend.pixels);
    free(g_backend.zbuffer);
    SDL_DestroyTexture(g_backend.texture);
    SDL_DestroyRenderer(g_backend.renderer);
    SDL_DestroyWindow(g_backend.window);
    fprintf(stderr, "Video destroyed successfully\n");
    fprintf(stderr, "Exiting...\n");
    SDL_Quit();
    exit(0);
}

static void clear_pixel_buffer() {
    memset(g_backend.pixels, 0, g_backend.screen_size[0] * g_backend.screen_size[1] * sizeof(uint32_t));
}

static void clear_zbuffer() {
    for (int i = g_backend.screen_size[0] * g_backend.screen_size[1]; i--;) {
        g_backend.zbuffer[i] = -FLT_MAX;
    }
}

void clear_screen() {
    clear_zbuffer();
    clear_pixel_buffer();
}
