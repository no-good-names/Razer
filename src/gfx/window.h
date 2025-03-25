//
// Created by cp176 on 3/15/2025.
//

#ifndef WINDOW_H
#define WINDOW_H

#include <stdbool.h>
#include <stdint.h>
#include <SDL2/SDL.h>

struct dt {
	float current;
	float last;
	float deltaTime;
};

extern struct dt dt;
extern uint32_t *pixels;
extern int screen_size[2];
extern float aspect_ratio[2];
extern SDL_Window *window;
extern SDL_Renderer *renderer;
extern SDL_Texture *texture;
extern bool running;

#define PIXELS_SIZE screen_size[0] * screen_size[1] * sizeof(uint32_t)

void init_renderer(int width, int height);
void update_events();
void update_renderer();
void destroy_renderer();

#endif //WINDOW_H
