#ifndef BACKEND_H
#define BACKEND_H

#include <stdbool.h>
#include <stdint.h>
#include <SDL2/SDL.h>

extern uint32_t *pixels;
extern SDL_Window *window;
extern SDL_Renderer *renderer;
extern SDL_Texture *texture;
extern bool quit;
extern int screen_size[2];
extern int window_size[2];
extern float aspect_ratio[2];
void init_video(uint16_t w, uint16_t h, uint16_t window_scale);
void update_events();
void update_video();
void destroy_video();
static int get_screen_width() {
    return screen_size[0];
}
static int get_screen_height() {
    return screen_size[1];
}
static int get_window_width() {
    return window_size[0];
}
static int get_window_height() {
    return window_size[1];
}

static void clear_pixel_buffer() {
    memset(pixels, 1, get_screen_width() * get_screen_height() * sizeof(uint32_t));
}

#endif
