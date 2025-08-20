#ifndef BACKEND_H
#define BACKEND_H

#include <stdbool.h>
#include <stdint.h>
#include <SDL2/SDL.h>

struct global_backend{
	uint32_t *pixels;
	float *zbuffer;
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Texture *texture;
	bool quit;
	int screen_size[2];
	int window_size[2];
	float aspect_ratio[2];
};

struct global_backend *get_backend_state();

void init_video(uint16_t window_width, uint16_t window_height,
	uint16_t screen_width, uint16_t screen_height);
void update_events();
void update_video();
void destroy_video();

inline int get_screen_width() { return get_backend_state()->screen_size[0]; }
inline int get_screen_height() { return get_backend_state()->screen_size[1]; }
inline int get_window_width() { return get_backend_state()->window_size[0]; }
inline int get_window_height() { return get_backend_state()->window_size[1]; }

static void clear_pixel_buffer();

static void clear_zbuffer();

void clear_screen();

#endif
