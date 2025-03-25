//
// Created by cp176 on 3/15/2025.
//

#include <SDL2/SDL.h>
#include <stdio.h>

#include "gfx/gfx.h"

int main(int argc, char *argv[]) {
	init_renderer(800, 600);

	vec2 points[3] = {
        {0.0f, 0.5f},
        {0.5f, -0.5f},
        {-0.5f, -0.5f}
    };

	SetDrawType(TRIANGLE_FILLED);

	while (running) {
		update_events();
		memset(pixels, 0, PIXELS_SIZE);
		DrawTriangle(points, RGB(255, 0, 0));

		const uint8_t *keys = SDL_GetKeyboardState(NULL);
		if (keys[SDL_SCANCODE_ESCAPE]) {
            running = false;
        }

		update_renderer();
	}
	destroy_renderer();
	return 0;
}
