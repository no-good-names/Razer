//
// Created by cp176 on 2/9/2025.
//

#ifndef WINDOW_H
#define WINDOW_H

#include <stdbool.h>
#include <stdint.h>
#include <SDL2/SDL.h>

struct screen_size {
	int x, y;
};

struct aspect_ratio {
	float x, y;
};

struct dt {
	float current;
	float last;
	float deltaTime;
};

extern struct dt dt;
extern uint32_t *pixels;
extern struct screen_size screen_size;
extern struct aspect_ratio aspect_ratio;
extern SDL_Window *window;
extern SDL_Renderer *renderer;
extern SDL_Texture *texture;
extern bool running;

#define PIXELS_SIZE screen_size.x * screen_size.y * sizeof(uint32_t)

void init_renderer(int width, int height);
void updateEvents();
void updateWindow();
void destroyWindow();

#endif //WINDOW_H
